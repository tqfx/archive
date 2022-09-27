//! proportional integral derivative controller

use crate::Real;
use crate::Uint;

/// turn off PID controller
pub const OFF: Uint = 0;
/// positional PID controller
pub const POS: Uint = 1;
/// incremental PID controller
pub const INC: Uint = 2;

/// proportional integral derivative controller
#[repr(C)]
pub struct PID {
    /// sampling time unit(s)
    pub ts: Real,
    /// proportional constant
    pub kp: Real,
    /// integral constant
    pub ki: Real,
    /// derivative constant
    pub kd: Real,
    /// controller output
    pub out: Real,
    /// (integral) output item sum
    pub sum: Real,
    /// cache feedback
    pub fdb: Real,
    /// error change
    pub ec: Real,
    /// error input
    pub e: Real,
    /// minimum output
    pub outmin: Real,
    /// maximum output
    pub outmax: Real,
    /// maximum integral output
    pub summax: Real,
    num: Uint,
    reg: Uint,
}

extern "C" {
    fn a_pid_off(ctx: *mut PID) -> *mut PID;
    fn a_pid_inc(ctx: *mut PID) -> *mut PID;
    fn a_pid_pos(ctx: *mut PID, max: Real) -> *mut PID;
    fn a_pid_mode(ctx: *mut PID, reg: Uint) -> *mut PID;
    fn a_pid_time(ctx: *mut PID, ts: Real) -> *mut PID;
    fn a_pid_kpid(ctx: *mut PID, kp: Real, ki: Real, kd: Real) -> *mut PID;
    fn a_pid_cc_x(ctx: *mut PID, set: Real, fdb: Real) -> Real;
    fn a_pid_zero(ctx: *mut PID) -> *mut PID;
}

/**
## Examples

```no_run
let mut pid = liba::PID::new(1.0, -10.0, 10.0);
pid.mode(liba::pid::OFF);
pid.mode(liba::pid::POS);
pid.mode(liba::pid::INC);
pid.kpid(10.0, 0.1, 1.0);
pid.time(0.1);
pid.pos(10.0);
pid.off();
pid.inc();
pid.proc(1.0, 0.0);
pid.zero();
```
*/
impl PID {
    /// initialize function for PID controller, default is turn off
    pub fn new(ts: Real, outmin: Real, outmax: Real) -> Self {
        Self {
            ts,
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
            out: 0.0,
            outmin,
            outmax,
            sum: 0.0,
            summax: 0.0,
            e: 0.0,
            ec: 0.0,
            fdb: 0.0,
            reg: OFF,
            num: 0,
        }
    }

    /// initialize function for positional PID controller
    pub fn new_pos(
        ts: Real,
        kp: Real,
        ki: Real,
        kd: Real,
        outmin: Real,
        outmax: Real,
        summax: Real,
    ) -> Self {
        Self {
            ts,
            kp,
            ki,
            kd,
            out: 0.0,
            outmin,
            outmax,
            sum: 0.0,
            summax,
            e: 0.0,
            ec: 0.0,
            fdb: 0.0,
            reg: POS,
            num: 0,
        }
    }

    /// initialize function for incremental PID controller
    pub fn new_inc(ts: Real, kp: Real, ki: Real, kd: Real, outmin: Real, outmax: Real) -> Self {
        Self {
            ts,
            kp,
            ki,
            kd,
            out: 0.0,
            outmin,
            outmax,
            sum: 0.0,
            summax: 0.0,
            e: 0.0,
            ec: 0.0,
            fdb: 0.0,
            reg: INC,
            num: 0,
        }
    }

    /// turn off PID controller
    pub fn off(&mut self) -> &mut Self {
        unsafe { a_pid_off(self).as_mut().unwrap_unchecked() }
    }

    /// incremental PID controller
    pub fn inc(&mut self) -> &mut Self {
        unsafe { a_pid_inc(self).as_mut().unwrap_unchecked() }
    }

    /// positional PID controller
    pub fn pos(&mut self, max: Real) -> &mut Self {
        unsafe { a_pid_pos(self, max).as_mut().unwrap_unchecked() }
    }

    /// set register for PID controller directly
    pub fn mode(&mut self, reg: u32) -> &mut Self {
        unsafe { a_pid_mode(self, reg as Uint).as_mut().unwrap_unchecked() }
    }

    /// set sampling period for PID controller
    pub fn time(&mut self, ts: Real) -> &mut Self {
        unsafe { a_pid_time(self, ts).as_mut().unwrap_unchecked() }
    }

    /// set proportional integral derivative constant for PID controller
    pub fn kpid(&mut self, kp: Real, ki: Real, kd: Real) -> &mut Self {
        unsafe { a_pid_kpid(self, kp, ki, kd).as_mut().unwrap_unchecked() }
    }

    /// process function for PID controller
    pub fn proc(&mut self, set: Real, fdb: Real) -> Real {
        unsafe { a_pid_cc_x(self, set, fdb) }
    }

    /// zero function for PID controller
    pub fn zero(&mut self) -> &mut Self {
        unsafe { a_pid_zero(self).as_mut().unwrap_unchecked() }
    }
}
