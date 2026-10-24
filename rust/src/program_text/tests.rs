// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::*;
use crate::compiler::Real;

fn roundtrip(program: &Program) -> EncodedProgram {
    let encoded = encode(program).unwrap();
    let decoded = decode(&encoded.text, |hash, _| Ok(encoded.blobs[hash].clone())).unwrap();
    assert_eq!(
        semantic_digest(program).unwrap(),
        semantic_digest(&decoded).unwrap()
    );
    assert_eq!(encoded.text, encode(&decoded).unwrap().text);
    encoded
}
fn program(floats: Vec<Real>) -> Program {
    let mut graph = Graph::default();
    graph.values.insert(
        "weights \"λ\"".into(),
        Value {
            floats,
            constant: true,
            ..Default::default()
        },
    );
    Program {
        phases: BTreeMap::from([("model".into(), graph)]),
        ..Default::default()
    }
}

#[test]
fn numeric_bits_defaults_and_repeats() {
    let bits = [
        0,
        1 << 63,
        1,
        u64::MAX,
        0x7ff0000000000000,
        0xfff0000000000000,
        0x7ff0000000000001,
        0x7ff8000000000042,
        0x3fb999999999999a,
        0x3d719799a0000000,
    ];
    let source = roundtrip(&program(bits.map(Real).to_vec())).text;
    assert!(source.contains("real(-0.0)"));
    assert!(source.contains("bits(\"7ff8000000000042\")"));
    assert!(!source.contains("options"));
    assert!(roundtrip(&program(vec![Real(1 << 63); 100]))
        .text
        .contains("repeat(real(-0.0), 100)"));
    let mut state = 1u64;
    for _ in 0..1000 {
        state = state
            .wrapping_mul(6364136223846793005)
            .wrapping_add(1442695040888963407);
        roundtrip(&program(vec![Real(state)]));
    }
}

#[test]
fn shared_tables_quantization_and_chunks() {
    let floats = (0..CHUNK_BYTES / 8 + 17)
        .map(|i| Real(i as u64))
        .collect::<Vec<_>>();
    let mut p = program(floats.clone());
    let graph = p.phases.get_mut("model").unwrap();
    let q = Quantization {
        axis: -1,
        scales: floats,
        zeros: vec![0; 20],
        ..Default::default()
    };
    for name in ["x", "y"] {
        graph.values.insert(
            name.into(),
            Value {
                tensor: TensorType {
                    dtype: Dtype::I8,
                    shape: vec![
                        Expr::Symbol(0),
                        Expr::Mul(vec![Expr::Known(2), Expr::Known(3)]),
                    ],
                    quant: Some(q.clone()),
                },
                ..Default::default()
            },
        );
    }
    let encoded = roundtrip(&p);
    assert_eq!(encoded.blobs.len(), 2);
    assert!(encoded
        .blobs
        .values()
        .all(|bytes| bytes.len() <= CHUNK_BYTES));
    assert_eq!(encoded.text.matches("  quant q").count(), 1);
    assert_eq!(encoded.text.matches("array a").count(), 1);
    let mut corrupt = encoded.blobs.clone();
    corrupt.values_mut().next().unwrap()[0] ^= 1;
    assert!(decode(&encoded.text, |hash, _| Ok(corrupt[hash].clone()))
        .unwrap_err()
        .to_string()
        .contains("identity mismatch"));
}

#[test]
fn sparse_options_and_nested_graphs() {
    let mut p = program(vec![]);
    p.options.cleanup = false;
    p.phase_options
        .insert("model".into(), CompileOptions::default());
    p.phases
        .get_mut("model")
        .unwrap()
        .functions
        .insert("inner".into(), Graph::default());
    let source = roundtrip(&p).text;
    assert!(source.contains("options {cleanup: false}"));
    assert!(source.contains("phase_options \"model\" {}"));
}

#[test]
fn rejects_ambiguous_unbounded_or_unknown_source() {
    let empty = "phase model { inputs (); outputs (); }";
    for body in [
        format!("{empty} {empty}"),
        "phase model { inputs (); inputs (); outputs (); }".into(),
        "phase model { inputs (); outputs (); const w: f32[1] floats repeat(real(1.0), 16000001); }".into(),
        format!("options {{cleanup: true, cleanup: false}}; {empty}"),
        format!("options {{typo: true}}; {empty}"),
        format!("array a0 = r64(0, 10); {empty}"),
        "phase model { inputs (); outputs (); value w: f32[1] quant missing; }".into(),
        "phase model { inputs (); outputs (); const w: f32[1] floats [real(1e999)]; }".into(),
        "phase model { inputs (); outputs (); const w: f32[1] floats [bits(\"xyz\")]; }".into(),
        format!("blob \"../bad\" 8; {empty}"),
    ] {
        let source = format!("ynn_program 1 {{ {body} }}");
        assert!(decode(&source, |_, _| panic!("Unvalidated path reached loader")).is_err(), "{source}");
    }
    assert!(decode(
        &format!("ynn_program 1 {{ {empty} }} trailing"),
        |_, _| unreachable!()
    )
    .is_err());
    assert!(decode("ynn_program 2 {}", |_, _| unreachable!()).is_err());
}
