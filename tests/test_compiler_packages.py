# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Package integrity tests exercise actual public plan validation."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'python'))
from ynnpack_assets.artifacts import publish


class PackageTest(unittest.TestCase):
    def fixture(self, root):
        raw=root/'raw';raw.mkdir();parameters=raw/'parameters';parameters.mkdir()
        payload=b'\x00\x00\x80\x3f';digest=hashlib.sha256(payload).hexdigest()
        data=parameters/(digest+'.bin');data.write_bytes(payload)
        plan=raw/'model.ynn'
        plan.write_text(f'''ynn 1 resource_contract=1 completion_contract=1 {{
weight w: storage<fp32[1]> = asset(path="@parameters/{digest}.bin", bytes=4, sha256="{digest}");
value y: storage<fp32[1]>;
output y;
Copy(input=w, output=y);
}}
''')
        model=dict(graphs=dict(model=dict(file=plan.name,sha256=hashlib.sha256(plan.read_bytes()).hexdigest())))
        (raw/'model.json').write_text(json.dumps(model))
        return raw,data

    def test_verified_package_is_atomic_and_existing_destination_is_preserved(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);raw,_=self.fixture(root);output=root/'package'
            publish(raw,output)
            before=(output/'model.ynn').read_bytes()
            with self.assertRaises(FileExistsError):publish(raw,output)
            self.assertEqual((output/'model.ynn').read_bytes(),before)

    def test_missing_or_tampered_payload_never_publishes(self):
        for mode in ('missing','tampered'):
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);raw,data=self.fixture(root);output=root/'package'
                if mode=='missing':data.unlink()
                else:data.write_bytes(b'bad!')
                with self.assertRaises(ValueError):publish(raw,output)
                self.assertFalse(output.exists())

    def test_phase_hash_is_checked_before_publication(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);raw,_=self.fixture(root);output=root/'package'
            (raw/'model.ynn').write_text((raw/'model.ynn').read_text()+'\n')
            with self.assertRaisesRegex(ValueError,'Phase hash'):publish(raw,output)
            self.assertFalse(output.exists())


if __name__=='__main__':
    unittest.main()
