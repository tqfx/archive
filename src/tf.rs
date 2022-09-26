//! transfer function

use crate::Real;
use crate::Uint;

/// transfer function
#[repr(C)]
pub struct TF {
    /// input
    u: *mut Real,
    /// output
    v: *mut Real,
    /// numerator
    num: *const Real,
    /// denominator
    den: *const Real,
    /// numerator number
    m: Uint,
    /// denominator number
    n: Uint,
}

extern "C" {
    fn a_tf_init(
        ctx: *mut TF,
        m: Uint,
        num: *const Real,
        u: *mut Real,
        n: Uint,
        den: *const Real,
        v: *mut Real,
    ) -> *mut TF;
    fn a_tf_proc(ctx: *mut TF, x: Real) -> Real;
    fn a_tf_zero(ctx: *mut TF) -> *mut TF;
}

/**
## Examples

```no_run
let num = [6.59492796e-05, 6.54019884e-05];
let den = [-1.97530991, 0.97530991];
let mut u = [0.0; 2];
let mut v = [0.0; 2];
let mut tf = liba::TF::new(&num, &mut u, &den, &mut v);
tf.proc(0.0);
tf.zero();
```
*/
impl TF {
    /// initialize function for transfer function
    pub fn new(num: &[Real], u: &mut [Real], den: &[Real], v: &mut [Real]) -> Self {
        let mut ctx: Self = Self {
            u: std::ptr::null_mut(),
            v: std::ptr::null_mut(),
            num: std::ptr::null(),
            den: std::ptr::null(),
            m: 0,
            n: 0,
        };
        unsafe {
            a_tf_init(
                &mut ctx,
                num.len() as Uint,
                num.as_ptr(),
                u.as_mut_ptr(),
                den.len() as Uint,
                den.as_ptr(),
                v.as_mut_ptr(),
            )
        };
        ctx
    }

    /// process function for transfer function
    pub fn proc(&mut self, x: Real) -> Real {
        unsafe { a_tf_proc(self, x) }
    }

    /// zero function for transfer function
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_tf_zero(self).as_mut().unwrap_unchecked() }
    }
}
