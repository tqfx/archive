//! An algorithm library based on C/C++ language
//!
//! ## Installation
//!
//! Add this to your `Cargo.toml`:
//!
//! ```toml
//! [dependencies]
//! liba = "0.1"
//! ```

#![deny(missing_docs)]

extern crate libc;

extern "C" {
    fn a_version() -> *const libc::c_char;
}

use std::ffi::CStr;
use std::str;

/// algorithm library version
///
/// ## Examples
///
/// ```no_run
/// fn main() {
///     println!("version {}", liba::version());
/// }
/// ```
pub fn version() -> String {
    let c_str: &CStr = unsafe { CStr::from_ptr(a_version()) };
    let str_slice: &str = c_str.to_str().unwrap();
    let str_buf: String = str_slice.to_owned();
    str_buf
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn run_version() {
        println!("version {}", version());
    }
}
