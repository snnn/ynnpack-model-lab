# Copyright 2026 @snnn
# SPDX-License-Identifier: Apache-2.0

from contextlib import redirect_stdout
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

from tools.check_publication import candidates, issues, main


class PublicationTest(unittest.TestCase):
    def test_host_path_and_contact(self):
        path = "/" + "home" + "/sample/project/build"
        email = "sample" + "@" + "example.org"
        problems = issues("results/log.txt", f"{path}\n{email}\n".encode())
        self.assertEqual([number for number, _ in problems], [1, 2])

    def test_email_address_formats(self):
        addresses = [
            ("sample", "example.org"),
            ("sample+benchmark", "example.org"),
            ("o'connor", "example.org"),
            ("x!#$%&'*+-/=?^_" + chr(96) + "{|}~", "example.org"),
            ('"two words"', "example.org"),
            ('"two@words"', "example.org"),
            ('"escaped\\"quote"', "example.org"),
            ("用户", "例子.公司"),
            ("e\u0301quipe", "example.org"),
            ("sample", "xn--fsqu00a.xn--55qx5d"),
            ("sample", "example." + "a" * 63),
            ("sample", "example.test"),
            ("sample", "[192.0.2.1]"),
            ("sample", "[IPv6:2001:db8::1]"),
        ]
        for local, domain in addresses:
            with self.subTest(local=local, domain=domain):
                email = local + "@" + domain
                self.assertEqual(issues("results/contact.txt", email.encode()),
                                 [(1, "personal email in file content")])

    def test_email_in_prose_markdown_and_code(self):
        email = "sample" + "@" + "example.org"
        contexts = [
            "Contact " + email + ".",
            "Contact " + email + "!",
            "User <" + email + ">",
            "'" + email + "'",
            '"' + email + '"',
            chr(96) + email + chr(96),
            "**" + email + "**",
            "_" + email + "_",
            "__" + email + "__",
            "[Contact](mailto:" + email + ")",
            "| Contact |" + email + "|",
            json.dumps({"contact": email}),
        ]
        for text in contexts:
            with self.subTest(text=text):
                self.assertEqual(issues("docs/contact.md", text.encode()),
                                 [(1, "personal email in file content")])

    def test_malformed_addresses_and_handles_are_not_emails(self):
        addresses = [
            (".sample", "example.org"),
            ("sample.", "example.org"),
            ("sample..name", "example.org"),
            ("sample", "example..org"),
            ("sample", "-example.org"),
            ("sample", "example-.org"),
            ("sample", "example_org"),
            ("sample" + "@", "example.org"),
            ("sample", "example.org" + "@" + "other.org"),
        ]
        texts = [local + "@" + domain for local, domain in addresses]
        texts += ["@" + "snnn", "actions/checkout" + "@v4"]
        for text in texts:
            with self.subTest(text=text):
                self.assertEqual(issues("docs/example.md", text.encode()), [])

    def test_json_escaped_addresses_are_checked(self):
        addresses = [
            "用户" + "@" + "例子.公司",
            '"two words"' + "@" + "example.org",
        ]
        for email in addresses:
            for document in ({"contacts": [email]}, {email: "contact"}):
                with self.subTest(document=document):
                    problems = issues("results/contact.json", json.dumps(document).encode())
                    self.assertTrue(problems)
                    self.assertTrue(all(
                        "personal email" in category for _, category in problems
                    ))
                    self.assertNotIn(email, str(problems))

    def test_email_detection_does_not_query_dns(self):
        email = "sample" + "@" + "example.org"
        with mock.patch(
            "dns.resolver.Resolver.resolve", side_effect=AssertionError("DNS query")
        ) as resolve:
            self.assertEqual(issues("results/contact.txt", email.encode()),
                             [(1, "personal email in file content")])
            resolve.assert_not_called()

    def test_cli_does_not_disclose_email(self):
        email = "sample" + "@" + "example.org"
        output = io.StringIO()
        records = [("results/contact.txt", email.encode())]
        with mock.patch("sys.argv", ["check_publication.py"]), \
             mock.patch("tools.check_publication.candidates", return_value=iter(records)), \
             redirect_stdout(output):
            self.assertTrue(main())
        self.assertIn("results/contact.txt:1: personal email", output.getvalue())
        self.assertNotIn(email, output.getvalue())

    def test_missing_dependency_fails_with_setup_instructions(self):
        root = Path(__file__).resolve().parents[1]
        result = subprocess.run(
            [sys.executable, "-S", "tools/check_publication.py"],
            cwd=root, capture_output=True, text=True,
        )
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("uv run --locked", result.stderr)
        self.assertNotIn("Traceback", result.stderr)
        self.assertEqual(result.stdout, "")

    def test_device_metadata_preserves_model_and_firmware(self):
        record = {"device": "Pixel 8", "firmware": "Android 17", "serial": "device-001"}
        self.assertEqual(len(issues("results/device.json", json.dumps(record).encode())), 1)
        record["serial"] = "${ANDROID_SERIAL}"
        self.assertEqual(issues("results/device.json", json.dumps(record).encode()), [])

    def test_notices_and_portable_commands(self):
        email = "upstream" + "@" + "example.org"
        self.assertEqual(issues("third_party/LICENSE", email.encode()), [])
        self.assertEqual(issues("source.cc", ("// Copyright 2026 " + email).encode()), [])
        self.assertEqual(issues("docs/example.md", b'adb -s "$ANDROID_SERIAL" shell true'), [])
        command = b"adb" + b" -s device-001 shell true"
        self.assertEqual(len(issues("docs/example.md", command)), 1)

    def test_private_artifacts_and_credentials(self):
        self.assertTrue(issues("out/capture.json", b"{}"))
        self.assertTrue(issues("models/model/authoring/model.py", b""))
        self.assertTrue(issues("AGENTS.md", b""))
        record = {"api_key": "example-secret", "files": {"patches/core-ir-example.patch": "hash"}}
        self.assertEqual(len(issues("results/environment.json", json.dumps(record).encode())), 2)

    def test_binary_fixture_and_public_sources(self):
        self.assertEqual(issues("tests/tokenizers/sp/tokenizer.model", b"\0\x01"), [])
        self.assertEqual(issues("models/model/generated/model.cc", b"// standalone builder\n"), [])
        self.assertTrue(issues("assets/model.safetensors", b"\0\x01"))

    def test_staged_content_is_checked_independently_of_worktree(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            subprocess.run(["git", "init", "-q", directory], check=True)
            path = root / "device.json"
            path.write_text('{"serial":"device-001"}')
            subprocess.run(["git", "add", "device.json"], cwd=root, check=True)
            path.write_text('{"device":"Pixel 8"}')
            self.assertFalse(any(issues(name, data) for name, data in candidates(root)))
            self.assertTrue(any(issues(name, data) for name, data in candidates(root, staged=True)))


if __name__ == "__main__":
    unittest.main()
