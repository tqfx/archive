const std = @import("std");

const flags = [_][]const u8{
    "-Wall",
    "-Wextra",
    "-pedantic",
};

const sources = [_][]const u8{
    "src/arr.c",
    "src/complex.c",
    "src/crc.c",
    "src/fpid.c",
    "src/fuzzy.c",
    "src/lib.c",
    "src/math.c",
    "src/mf.c",
    "src/pid.c",
    "src/poly.c",
    "src/polytrack.c",
    "src/real.c",
    "src/tf.c",
    "src/version.c",
    "src/version.cpp",
    "src/host/que.c",
    "src/host/str.c",
    "src/host/vec.c",
    "src/host/vector.c",
};

pub fn build(b: *std.build.Builder) void {
    const mode = b.standardReleaseOptions();
    const lib = b.addStaticLibrary("a", null);
    lib.addCSourceFiles(&sources, &flags);
    lib.defineCMacro("A_EXPORTS", null);
    lib.addIncludePath("include");
    lib.linkSystemLibrary("m");
    lib.setBuildMode(mode);
    lib.install();
}
