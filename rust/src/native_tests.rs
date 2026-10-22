// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use crate::{ffi, vision::VisionBuilder, ErrorKind, Result};
use std::path::Path;

pub(crate) fn run(args: &[String]) -> Result<()> {
    let model = Path::new(&args[1]);
    assert!(VisionBuilder::load(model)?.prepare(0).is_err());
    for threads in [1, 4] {
        let plan = model.join("square.ynn");
        for source in [None, Some(plan.as_path())] {
            let mut session = VisionBuilder::load_with_plan(model, source)?.prepare(threads)?;
            session.input_mut().copy_from_slice(&[-3.0, 0.5, 0.0, 4.0]);
            assert_eq!(session.run()?, &[9.0, 0.25, 0.0, 16.0]);
            session.input_mut().copy_from_slice(&[2.0, -2.0, 1.0, 8.0]);
            assert_eq!(session.run()?, &[4.0, 4.0, 1.0, 64.0]);
        }
    }
    let assets = ffi::Assets::open(Path::new(""), Path::new(""))?;
    assert_eq!(
        ffi::GraphBuilder::native_fixture(assets.clone(), 999)
            .err()
            .unwrap()
            .kind,
        ErrorKind::Invalid
    );
    // Releasing the caller's asset handle does not release a graph's owner.
    let graph = ffi::GraphBuilder::native_fixture(assets.clone(), 0)?;
    drop(assets);
    let mut input = ffi::Buffer::new(4, 1.0f32);
    let mut too_small = ffi::Buffer::new(1, 0.0f32);
    let mut graph = graph.prepare(1)?;
    unsafe {
        graph.bind(&ffi::string("x")?, &mut input, &[4], false)?;
        graph.bind(&ffi::string("squared")?, &mut too_small, &[], false)?;
    }
    // Native validation must reject undersized output before touching it.
    assert!(graph.run().is_err());
    assert_eq!(&*too_small, &[0.0]);
    drop(graph); // native borrows end before stack storage
    mapped_constant_lifetime()?;
    loaded_constant_lifetime()?;
    crate::runtime::tests::preparation()?;
    for capacity in [2048, 8448] {
        for threads in [1, 4] {
            state_checks(capacity, threads, &model.join("../generated"))?;
        }
    }
    let plans = model.join("../generated");
    let output = std::env::temp_dir().join(format!("ynnpack-state-{}", std::process::id()));
    std::fs::create_dir(&output)?;
    for threads in [1, 4] {
        for (capacity, heads, window, queries) in [
            (2048, 1, 512, 1),
            (2048, 2, 512, 2),
            (8448, 2, 512, 2),
            (8448, 4, 512, 4),
            (2048, 2, 0, 2),
            (2048, 2, 1, 2),
            (2048, 1, 512, 4),
            (2048, 2, 512, 8),
            (8448, 2, 0, 8),
        ] {
            let suffix = if queries == heads {
                String::new()
            } else {
                format!("_q{queries}")
            };
            let name = format!("c{capacity}_h{heads}_w{window}{suffix}");
            let assets = ffi::Assets::open(Path::new(""), &plans.join("parameters"))?;
            ffi::GraphBuilder::from_plan(assets, &plans.join(format!("{name}.ynn")))?
                .state_fixture(
                    capacity,
                    heads,
                    window,
                    threads,
                    &output.join(format!("{name}_t{threads}.ir.txt")),
                    queries,
                )?;
        }
    }
    std::fs::remove_dir_all(output)?;
    println!("Rust/native ownership and arithmetic checks passed");
    Ok(())
}

fn mapped_constant_lifetime() -> Result<()> {
    let path = std::env::temp_dir().join(format!("ynnpack-rust-{}", std::process::id()));
    std::fs::create_dir(&path)?;
    std::fs::write(path.join("scale.bin"), 3.0f32.to_le_bytes())?;
    let assets = ffi::Assets::open(&path, &path)?;
    let builder = ffi::GraphBuilder::native_fixture(assets.clone(), 3)?;
    drop(assets);
    // Unix mappings keep file contents alive after unlink. Graph's Rc must keep
    // the mapping alive through compilation and execution, not just creation.
    std::fs::remove_file(path.join("scale.bin"))?;
    std::fs::remove_dir(&path)?;
    let input = ffi::Buffer::new(4, 2.0f32);
    let output = ffi::Buffer::new(4, 0.0f32);
    let mut graph = builder.prepare(1)?;
    unsafe {
        graph.bind(c"x", &input, &[4], false)?;
        graph.bind(c"squared", &output, &[], false)?;
    }
    graph.run()?;
    assert_eq!(&*output, &[6.0; 4]);
    drop(graph);
    Ok(())
}

fn loaded_constant_lifetime() -> Result<()> {
    let path = std::env::temp_dir().join(format!("ynnpack-plan-{}", std::process::id()));
    std::fs::create_dir(&path)?;
    std::fs::write(path.join("scale.bin"), 3.0f32.to_le_bytes())?;
    let mut plan = format!(
        r#"ynn 1 resource_contract=1 completion_contract=1 {{
        input x: fp32[4];
        weight scale: fp32[1] = asset(path="@parameters/scale.bin", bytes=4, sha256="{}");
        let out: storage<fp32[4]> = mul(x, scale);
        output out;
    }}"#,
        "0".repeat(64)
    );
    let file = path.join("graph.ynn");
    std::fs::write(&file, &plan)?;
    let error = ffi::GraphBuilder::from_plan(ffi::Assets::open(&path, &path)?, &file)
        .err()
        .expect("mismatched mapped bytes must be rejected");
    assert!(error.to_string().contains("Constant hash mismatch"));
    plan = plan.replace(
        &"0".repeat(64),
        "ea2845900b5856c9bf354b1aa9761b5aa6888e5ed61738fe9579ca42bc0f6054",
    );
    std::fs::write(&file, &plan)?;
    let assets = ffi::Assets::open(&path, &path)?;
    let builder = ffi::GraphBuilder::from_plan(assets.clone(), &file)?;
    drop(assets);
    std::fs::remove_file(path.join("scale.bin"))?;
    std::fs::remove_file(file)?;
    std::fs::remove_dir(path)?;
    let input = ffi::Buffer::new(4, 2.0f32);
    let output = ffi::Buffer::new(4, 0.0f32);
    let mut graph = builder.prepare(1)?;
    unsafe {
        graph.bind(c"x", &input, &[4], false)?;
        graph.bind(c"out", &output, &[], false)?;
    }
    graph.run()?;
    assert_eq!(&*output, &[6.0; 4]);
    drop(graph);
    Ok(())
}

struct StateFixture {
    graph: ffi::PreparedGraph,
    states: [ffi::Resource; 3],
    q: ffi::Buffer<f32>,
    fresh: ffi::Buffer<f32>,
    output: ffi::Buffer<f32>,
    knew: ffi::Buffer<i8>,
    vnew: ffi::Buffer<i8>,
    capacity: usize,
}
const NAMES: [&std::ffi::CStr; 3] = [c"kcache", c"vcache", c"onlycache"];
impl StateFixture {
    fn new(capacity: usize, threads: usize, plans: &Path) -> Result<Self> {
        let assets = ffi::Assets::open(Path::new(""), &plans.join("parameters"))?;
        let builder =
            ffi::GraphBuilder::from_plan(assets, &plans.join(format!("c{capacity}_h2_w512.ynn")))?;
        let graph = builder.prepare(threads)?;
        let mut states = Vec::new();
        for name in NAMES {
            states.push(ffi::Resource::new(&graph, name, &[1, 2, capacity, 8])?);
        }
        Ok(Self {
            graph,
            states: states.try_into().ok().unwrap(),
            q: ffi::Buffer::new(2048, 0.0),
            fresh: ffi::Buffer::new(2048, 0.0),
            output: ffi::Buffer::new(2048, 0.0),
            knew: ffi::Buffer::new(2112, 0),
            vnew: ffi::Buffer::new(2112, 0),
            capacity,
        })
    }
    fn reset(&mut self) -> Result<()> {
        for state in &mut self.states {
            state.reset()?;
        }
        Ok(())
    }
    fn bind(&mut self, p: usize, rows: usize) -> Result<()> {
        for h in 0..2 {
            for t in 0..rows {
                for d in 0..8 {
                    let index = (h * rows + t) * 8 + d;
                    self.fresh[index] = code(h, p + t, d) as f32 / 32.0;
                    self.q[index] = ((h * 3 + (p + t) * 5 + d) % 13) as f32 / 16.0;
                }
            }
        }
        self.graph.scalar(c"position", p as i64)?;
        unsafe {
            self.graph
                .bind(c"q", &mut self.q, &[1, 2, rows, 8], false)?;
            self.graph
                .bind(c"fresh", &mut self.fresh, &[1, 2, rows, 8], false)?;
            self.graph.bind(c"result", &mut self.output, &[], false)?;
            self.graph.bind(c"knew", &mut self.knew, &[], false)?;
            self.graph.bind(c"vnew", &mut self.vnew, &[], false)?;
            for (name, state) in NAMES.iter().zip(&mut self.states) {
                self.graph.resource(name, state)?;
            }
        }
        Ok(())
    }
    fn append(&mut self, p: usize, rows: usize) -> Result<()> {
        self.bind(p, rows)?;
        let before = self.graph.counters()?;
        self.graph.run()?;
        let after = self.graph.counters()?;
        assert_eq!(after.append_calls - before.append_calls, 3);
        assert_eq!(
            after.append_bytes - before.append_bytes,
            (3 * 2 * rows * 8) as u64
        );
        assert_eq!(after.view_copy_bytes, 0);
        // Independent packed-storage and attention oracle: use explicit physical
        // capacity strides and per-query window bounds, not adapter expressions.
        for h in 0..2 {
            for t in 0..rows {
                for d in 0..8 {
                    let at = (h * self.capacity + p + t) * 8 + d;
                    assert_eq!(self.states[0].data()[at], code(h, p + t, d));
                    assert_eq!(self.states[1].data()[at], 2 * code(h, p + t, d));
                    assert_eq!(self.states[2].data()[at], code(h, p + t, d));
                }
                let begin = (p + t).saturating_sub(511);
                let end = p + t + 1;
                let mut scores = Vec::new();
                for history in begin..end {
                    let score: f64 = (0..8)
                        .map(|d| {
                            self.q[(h * rows + t) * 8 + d] as f64 * code(h, history, d) as f64
                                / 32.0
                        })
                        .sum();
                    scores.push((score / 8f64.sqrt()).exp());
                }
                let sum: f64 = scores.iter().sum();
                for d in 0..8 {
                    let mut expected: f64 = scores
                        .iter()
                        .enumerate()
                        .map(|(i, &s)| s / sum * (2 * code(h, begin + i, d)) as f64 / 32.0)
                        .sum();
                    for z in 0..8 {
                        expected += self.q[(h * rows + t) * 8 + z] as f64
                            * if z == d {
                                0.2
                            } else {
                                0.01 * (z as f64 - d as f64)
                            };
                    }
                    let actual = self.output[(h * rows + t) * 8 + d];
                    assert!(
                        actual.is_finite() && (actual as f64 - expected).abs() < 2e-4,
                        "p={p} rows={rows} h={h} t={t} d={d}: {actual} != {expected}"
                    );
                }
            }
        }
        Ok(())
    }
}
fn code(h: usize, t: usize, d: usize) -> i8 {
    ((h * 13 + t * 7 + d * 3) % 17) as i8 - 8
}
fn state_checks(capacity: usize, threads: usize, plans: &Path) -> Result<()> {
    let mut f = StateFixture::new(capacity, threads, plans)?;
    for length in [1, 128, 129, 130, 511, 512, 513, 1024] {
        f.reset()?;
        let mut p = 0;
        while p < length - 1 {
            let rows = (length - 1 - p).min(128);
            f.append(p, rows)?;
            p += rows;
        }
        f.append(p, 1)?;
    }
    // A changed scalar with identical shapes must still reject a stale prefix.
    f.bind(1025, 1)?;
    let before: Vec<_> = f.states.iter().map(|s| s.data().to_vec()).collect();
    assert!(f.graph.run().is_err());
    for (state, saved) in f.states.iter().zip(&before) {
        assert_eq!(state.data(), saved);
    }
    f.reset()?;
    // Reset invalidates previously bound epochs, even at the correct position.
    f.graph.scalar(c"position", 0)?;
    assert!(f.graph.run().is_err());
    f.append(0, 1)?;
    for state in &mut f.states {
        state.import(capacity - 1)?;
    }
    f.bind(capacity - 1, 1)?;
    f.graph.run()?;
    let before: Vec<_> = f.states.iter().map(|s| s.data().to_vec()).collect();
    f.bind(capacity, 1)?;
    assert!(f.graph.run().is_err());
    for (state, saved) in f.states.iter().zip(&before) {
        assert_eq!(state.data(), saved);
    }
    // The backend may have mutated a subset of storage before an error. Native
    // publication poisons the graph; a reset cannot make that graph reusable.
    f.reset()?;
    f.bind(0, 2)?;
    f.graph.fail_after_appends(1)?;
    assert!(f.graph.run().is_err());
    f.reset()?;
    f.bind(0, 1)?;
    assert!(f.graph.run().is_err());
    Ok(())
}
