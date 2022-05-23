use cmake::Config;

fn main() {
    let mut config = Config::new(".");

    config.define("BUILD_TESTING", "0");

    config.static_crt(true);

    let dst = config.build();

    println!("cargo:rustc-link-search=native={}/lib", dst.display());
    println!("cargo:rustc-link-lib=static=a");
}
