# Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
"""Semantic package integrity and atomic publication, without target compilation."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'python'))
from ynnpack_assets.artifacts import publish, read_program, seal, write_program, semantic_files

class PackageTest(unittest.TestCase):
    def fixture(self, root):
        raw=root/'raw';raw.mkdir();parameters=raw/'parameters';parameters.mkdir()
        payload=b'\x00\x00\x80\x3f';digest=hashlib.sha256(payload).hexdigest()
        data=parameters/(digest+'.bin');data.write_bytes(payload)
        program={'version':1,'phases':{'model':{'values':{'w':{'tensor':{'dtype':'f32','shape':[{'known':1}]},
            'constant':True,'data':{'path':'@parameters/'+data.name,'bytes':4,'sha256':digest}}},
            'inputs':[],'outputs':['w'],'nodes':[]}}}
        program['phases']['model']['values']['table'] = dict(tensor=dict(dtype='f32',shape=[dict(known=20)]),constant=True,integers=list(range(20)))
        write_program(program, raw/'program.ynn')
        (raw/'execution.json').write_text(json.dumps({'format':'ynn-tensor-execution','version':1,'graphs':{'model':{'inputs':[], 'outputs':[{'name':'w','dtype':'fp32','shape':[1]}]}}}))
        seal(raw)
        return raw,data

    def test_publish_without_target_compiler_and_preserve_destination(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);raw,_=self.fixture(root);output=root/'package'
            # Only the source formatter is configured. No compiler is used.
            publish(raw,output)
            before=(output/'program.ynn').read_bytes()
            self.assertFalse((output/'program.json').exists())
            self.assertFalse((output/'program.json.gz').exists())
            self.assertEqual(read_program(raw),read_program(output))
            self.assertTrue(list((output/'program-data').glob('*.bin')))
            with self.assertRaises(FileExistsError):publish(raw,output)
            self.assertEqual((output/'program.ynn').read_bytes(),before)

    def test_missing_or_tampered_payload_never_publishes(self):
        for mode in ('missing','tampered'):
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);raw,data=self.fixture(root);output=root/'package'
                if mode=='missing':data.unlink()
                else:data.write_bytes(b'bad!')
                with self.assertRaises(ValueError):publish(raw,output)
                self.assertFalse(output.exists())

    def test_program_and_execution_hashes_are_checked(self):
        for file in ['program.ynn','execution.json']:
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

    def test_numeric_chunk_integrity_and_legacy_rejection(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);raw,_=self.fixture(root)
            chunk=next((raw/'program-data').glob('*.bin'));original=chunk.read_bytes()
            for content in [original+b'junk', original[:-1], bytes([original[0]^1])+original[1:]]:
                chunk.write_bytes(content)
                with self.assertRaises(ValueError):semantic_files(raw)
                with self.assertRaises(ValueError):publish(raw,root/'published')
            chunk.write_bytes(original)
            meta=json.loads((raw/'model.json').read_text());meta['package']['version']=1
            (raw/'model.json').write_text(json.dumps(meta))
            with self.assertRaisesRegex(ValueError,'version-2'):read_program(raw)

if __name__=='__main__':unittest.main()
