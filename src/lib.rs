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
    fn a_version_major() -> libc::c_uint;
    fn a_version_minor() -> libc::c_uint;
    fn a_version_patch() -> libc::c_uint;
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

/// algorithm library version major
///
/// ## Examples
///
/// ```no_run
/// fn main() {
///     println!("version {}", liba::version_major());
/// }
/// ```
pub fn version_major() -> u32 {
    let num: u32 = unsafe { a_version_major() as u32 };
    num
}

/// algorithm library version minor
///
/// ## Examples
///
/// ```no_run
/// fn main() {
///     println!("version {}", liba::version_minor());
/// }
/// ```
pub fn version_minor() -> u32 {
    let num: u32 = unsafe { a_version_minor() as u32 };
    num
}

/// algorithm library version patch
///
/// ## Examples
///
/// ```no_run
/// fn main() {
///     println!("version {}", liba::version_patch());
/// }
/// ```
pub fn version_patch() -> u32 {
    let num: u32 = unsafe { a_version_patch() as u32 };
    num
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn run_version() {
        println!("version {}", version());
    }
}
