// Copyright 2026 @snnn. SPDX-License-Identifier: Apache-2.0
use super::ExecutionSpec;
use serde_json::{json, Value};

fn fixture() -> Value {
    serde_json::from_str(include_str!("../../../../tests/llm_session/execution.json")).unwrap()
}

#[test]
fn requires_explicit_v2_compatibility() {
    let value = fixture();
    serde_json::from_value::<ExecutionSpec>(value.clone()).unwrap().validate().unwrap();
    for field in ["contract", "compatibility"] {
        let mut missing = value.clone();
        missing.as_object_mut().unwrap().remove(field);
        assert!(serde_json::from_value::<ExecutionSpec>(missing).is_err(), "{field}");
        let mut null = value.clone();
        null[field] = Value::Null;
        assert!(serde_json::from_value::<ExecutionSpec>(null).is_err(), "{field}");
    }
    for version in [0, 1, 3] {
        let mut unsupported = value.clone();
        unsupported["contract"] = json!(version);
        let spec: ExecutionSpec = serde_json::from_value(unsupported).unwrap();
        assert!(spec.validate().unwrap_err().message.contains("Unsupported model/runtime contract"));
    }
}

#[test]
fn rejects_unsupported_or_incomplete_compatibility() {
    for (field, replacement) in [
        ("backend", json!("other")),
        ("backend_api", json!(2)),
        ("artifact_abi", json!("unknown")),
        ("parameter_encoding", json!("big-endian")),
        ("required_features", json!([])),
        ("required_features", json!(["unsupported-feature"])),
        ("required_features", json!(["shape-preflight-v1", "shape-preflight-v1"])),
    ] {
        let mut value = fixture();
        value["compatibility"][field] = replacement;
        let spec: ExecutionSpec = serde_json::from_value(value).unwrap();
        assert!(spec.validate().is_err(), "{field}");
    }
}
