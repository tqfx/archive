//! An algorithm library based on C language.
//!
//! ## Installation
//!
//! Add this to your `Cargo.toml`:
//!
//! ```toml
//! [build-dependencies]
//! liba = "0.1"
//! ```

#![deny(missing_docs)]

extern crate cty;

use std::ffi::CStr;
use std::str;

extern "C" {
    fn a_version() -> *const cty::c_char;
}

/// library version
///
/// ## Examples
///
/// ```no_run
/// fn main() {
///     println!("version {}", a::version());
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
