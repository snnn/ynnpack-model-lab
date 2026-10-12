// Copyright 2026 @snnn.
// SPDX-License-Identifier: Apache-2.0
use super::*;
use crate::plan::{self, Arg, Data, Expr, ValidatedPlan};
use sha2::{Digest, Sha256};

#[repr(C)]
struct NativeArg {
    kind: u32,
    reserved: u32,
    integer: i64,
    real: f64,
    data: *const c_void,
    count: usize,
}
impl NativeArg {
    fn new(kind: u32) -> Self {
        Self {
            kind,
            reserved: 0,
            integer: 0,
            real: 0.0,
            data: std::ptr::null(),
            count: 0,
        }
    }
}
extern "C" {
    fn lab_assets_data(
        assets: *mut c_void,
        name: *const c_char,
        size: usize,
        out: *mut *const c_void,
        error: *mut NativeError,
    ) -> i32;
    fn lab_plan_create(values: usize, out: *mut *mut c_void, error: *mut NativeError) -> i32;
    fn lab_plan_expr(
        graph: *mut c_void,
        op: u32,
        literal: i64,
        children: *const u32,
        count: usize,
        out: *mut u32,
        error: *mut NativeError,
    ) -> i32;
    fn lab_plan_command(
        graph: *mut c_void,
        op: *const c_char,
        args: *const NativeArg,
        count: usize,
        error: *mut NativeError,
    ) -> i32;
}
impl Assets {
    fn verify(&self, d: &Data) -> Result<*const c_void> {
        let path = string(&d.path)?;
        let mut ptr = std::ptr::null();
        // SAFETY: native owner retains this immutable mapping; exact size was
        // checked by both artifact validation and the native file mapper.
        call(|e| unsafe {
            lab_assets_data(self.ptr.as_ptr(), path.as_ptr(), d.bytes, &mut ptr, e)
        })?;
        if ptr.is_null() {
            return Err(Error::invalid("Null constant mapping"));
        }
        if let Some((size, hash)) = self.verified.borrow().get(&d.path) {
            if *size != d.bytes || *hash != d.sha256 {
                return Err(Error::invalid("Conflicting constant identities"));
            }
            return Ok(ptr);
        }
        let bytes = unsafe { std::slice::from_raw_parts(ptr.cast::<u8>(), d.bytes) };
        let actual = format!("{:x}", Sha256::digest(bytes));
        if actual != d.sha256 {
            return Err(Error::invalid(format!(
                "Constant hash mismatch: {}",
                d.path
            )));
        }
        self.verified
            .borrow_mut()
            .insert(d.path.clone(), (d.bytes, d.sha256.clone()));
        Ok(ptr)
    }
}
struct Construction<'a> {
    graph: &'a NativeGraph,
    expressions: HashMap<Expr, u32>,
}
impl Construction<'_> {
    fn expr(&mut self, e: &Expr) -> Result<u32> {
        if let Some(id) = self.expressions.get(e) {
            return Ok(*id);
        }
        let (op, literal, xs) = match e {
            Expr::Known(v) => (0, *v, &[][..]),
            Expr::Symbol(v) => (1, i64::from(*v), &[][..]),
            Expr::Add(xs) => (2, 0, xs.as_slice()),
            Expr::Mul(xs) => (3, 0, xs.as_slice()),
            Expr::Min(xs) => (4, 0, xs.as_slice()),
            Expr::Max(xs) => (5, 0, xs.as_slice()),
            Expr::FloorDiv(xs) => (6, 0, xs.as_slice()),
            Expr::CeilDiv(xs) => (7, 0, xs.as_slice()),
        };
        let children = xs
            .iter()
            .map(|e| self.expr(e))
            .collect::<Result<Vec<_>>>()?;
        let mut id = 0;
        call(|err| unsafe {
            lab_plan_expr(
                self.graph.ptr.as_ptr(),
                op,
                literal,
                children.as_ptr(),
                children.len(),
                &mut id,
                err,
            )
        })?;
        self.expressions.insert(e.clone(), id);
        Ok(id)
    }
    fn command(&mut self, command: &plan::Command) -> Result<()> {
        let command = command.wire();
        // Heap allocations behind these vectors remain stable until the native
        // call returns. The native adapter copies attributes and expressions.
        let mut strings = Vec::<CString>::new();
        let mut ints = Vec::<Vec<i64>>::new();
        let mut floats = Vec::<Vec<f64>>::new();
        let mut texts = Vec::<Vec<*const c_char>>::new();
        let mut args = Vec::new();
        for arg in &command.args {
            let mut a = NativeArg::new(0);
            match arg {
                Arg::Int(v) => {
                    a.kind = 1;
                    a.integer = *v;
                }
                Arg::Native(v) => {
                    a.kind = 15;
                    a.integer = *v;
                }
                Arg::Text(v) | Arg::Dtype(v) | Arg::Binary(v) | Arg::Unary(v) | Arg::Reduce(v) => {
                    a.kind = match arg {
                        Arg::Text(_) => 2,
                        Arg::Dtype(_) => 3,
                        Arg::Binary(_) => 8,
                        Arg::Unary(_) => 9,
                        _ => 10,
                    };
                    strings.push(string(v)?);
                    a.data = strings.last().unwrap().as_ptr().cast();
                }
                Arg::Encoding(v) => {
                    a.kind = 2;
                    strings.push(string(&v.token())?);
                    a.data = strings.last().unwrap().as_ptr().cast();
                }
                Arg::Bool(v) => {
                    a.kind = 11;
                    a.integer = i64::from(*v);
                }
                Arg::Float(v) => {
                    a.kind = 12;
                    a.real = plan::float(v)?;
                }
                Arg::Ints(v) => {
                    a.kind = 4;
                    ints.push(v.clone());
                    a.data = ints.last().unwrap().as_ptr().cast();
                    a.count = v.len();
                }
                Arg::Floats(v) => {
                    a.kind = 13;
                    floats.push(
                        v.iter()
                            .map(|v| plan::float(v))
                            .collect::<Result<Vec<_>>>()?,
                    );
                    a.data = floats.last().unwrap().as_ptr().cast();
                    a.count = v.len();
                }
                Arg::Texts(v) => {
                    a.kind = 14;
                    let mut ptrs = Vec::new();
                    for s in v {
                        strings.push(string(s)?);
                        ptrs.push(strings.last().unwrap().as_ptr());
                    }
                    texts.push(ptrs);
                    a.data = texts.last().unwrap().as_ptr().cast();
                    a.count = v.len();
                }
                Arg::Expr(e) => {
                    a.kind = 6;
                    a.integer = i64::from(self.expr(e)?);
                }
                Arg::Exprs(es) => {
                    a.kind = 7;
                    ints.push(
                        es.iter()
                            .map(|e| self.expr(e).map(i64::from))
                            .collect::<Result<Vec<_>>>()?,
                    );
                    a.data = ints.last().unwrap().as_ptr().cast();
                    a.count = es.len();
                }
                Arg::Data(d) => {
                    a.kind = 5;
                    if let Some(d) = d {
                        a.data = self.graph._assets.verify(d)?;
                        a.count = d.bytes;
                    }
                }
            }
            args.push(a);
        }
        let name = string(command.op.name())?;
        call(|e| unsafe {
            lab_plan_command(
                self.graph.ptr.as_ptr(),
                name.as_ptr(),
                args.as_ptr(),
                args.len(),
                e,
            )
        })
    }
}
impl GraphBuilder {
    pub fn from_plan(assets: Rc<Assets>, path: &Path) -> Result<Self> {
        Self::from_validated_plan(assets, ValidatedPlan::read(path)?)
    }
    pub(crate) fn from_validated_plan(assets: Rc<Assets>, plan: ValidatedPlan) -> Result<Self> {
        // Verify all mapped data before allocating/mutating a native graph.
        for c in plan.commands() {
            for a in &c.wire().args {
                if let Arg::Data(Some(d)) = a {
                    assets.verify(d)?;
                }
            }
        }
        let mut ptr = std::ptr::null_mut();
        call(|e| unsafe { lab_plan_create(plan.value_count(), &mut ptr, e) })?;
        let graph = NativeGraph {
            ptr: NonNull::new(ptr).ok_or_else(|| Error::invalid("Null graph handle"))?,
            _assets: assets,
        };
        let mut construction = Construction {
            graph: &graph,
            expressions: HashMap::new(),
        };
        for (index, command) in plan.commands().iter().enumerate() {
            construction.command(command).map_err(|e| {
                Error::invalid(format!(
                    "Command {index} ({}): {e}",
                    command.wire().op.name()
                ))
            })?;
        }
        Ok(Self { graph })
    }
}
