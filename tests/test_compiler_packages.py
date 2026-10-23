# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Semantic package integrity and atomic publication, without target compilation."""
import gzip
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'python'))
from ynnpack_assets.artifacts import publish, read_program, seal

class PackageTest(unittest.TestCase):
    def fixture(self, root, compressed=False):
        raw=root/'raw';raw.mkdir();parameters=raw/'parameters';parameters.mkdir()
        payload=b'\x00\x00\x80\x3f';digest=hashlib.sha256(payload).hexdigest()
        data=parameters/(digest+'.bin');data.write_bytes(payload)
        program={'version':1,'phases':{'model':{'values':{'w':{'tensor':{'dtype':'f32','shape':[{'known':1}]},
            'constant':True,'data':{'path':'@parameters/'+data.name,'bytes':4,'sha256':digest}}},
            'inputs':[],'outputs':['w'],'nodes':[]}}}
        (raw/'program.json').write_text(json.dumps(program))
        (raw/'execution.json').write_text(json.dumps({'format':'ynn-tensor-execution','version':1,'graphs':{'model':{'inputs':[], 'outputs':[{'name':'w','dtype':'fp32','shape':[1]}]}}}))
        seal(raw,compress=compressed)
        return raw,data

    def test_publish_without_compiler_and_preserve_destination(self):
        for compressed in [False,True]:
            with self.subTest(compressed=compressed), tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);raw,_=self.fixture(root,compressed);output=root/'package'
                with patch('subprocess.run',side_effect=AssertionError('No compiler')):
                    publish(raw,output)
                file='program.json.gz' if compressed else 'program.json';before=(output/file).read_bytes()
                self.assertFalse(list(output.glob('*.ynn')))
                self.assertFalse((output/('program.json' if compressed else 'program.json.gz')).exists())
                with self.assertRaises(FileExistsError):publish(raw,output)
                self.assertEqual((output/file).read_bytes(),before)

    def test_missing_or_tampered_payload_never_publishes(self):
        for mode in ('missing','tampered'):
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);raw,data=self.fixture(root);output=root/'package'
                if mode=='missing':data.unlink()
                else:data.write_bytes(b'bad!')
                with self.assertRaises(ValueError):publish(raw,output)
                self.assertFalse(output.exists())

    def test_program_and_execution_hashes_are_checked(self):
        for file in ['program.json','execution.json']:
            with self.subTest(file=file), tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);raw,_=self.fixture(root);output=root/'package'
                (raw/file).write_text((raw/file).read_text()+'\n')
                with self.assertRaisesRegex(ValueError,'identity mismatch'):publish(raw,output)
                self.assertFalse(output.exists())

    def test_compiled_identity_and_wrong_phase_are_rejected(self):
        for change in [{'file':'model.ynn'},{'unexpected':{}}]:
            with tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);raw,_=self.fixture(root);output=root/'package'
                spec=json.loads((raw/'execution.json').read_text())
                if 'file' in change:spec['graphs']['model'].update(change)
                else:spec['graphs'].update(change)
                (raw/'execution.json').write_text(json.dumps(spec));seal(raw)
                with self.assertRaises(ValueError):publish(raw,output)
                self.assertFalse(output.exists())

    def test_one_complete_gzip_member_required(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);raw,_=self.fixture(root,compressed=True)
            path=raw/'program.json.gz';original=path.read_bytes()
            meta=json.loads((raw/'model.json').read_text())
            for content in [original+gzip.compress(b''),original+b'junk',original[:-4]]:
                path.write_bytes(content)
                meta['package']['program.json'].update(bytes=len(content),sha256=hashlib.sha256(content).hexdigest())
                (raw/'model.json').write_text(json.dumps(meta))
                with self.assertRaisesRegex(ValueError,'compressed semantic'):read_program(raw)
                with self.assertRaisesRegex(ValueError,'compressed semantic'):publish(raw,root/'published')

if __name__=='__main__':unittest.main()
