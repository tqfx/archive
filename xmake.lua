-- set project name
set_project("liba")

-- set xmake minimum version
set_xmakever("2.5.0")

-- set project version
set_version("0.1.1", {build = "%Y%m%d%H%M"})

-- set language: c11 c++11
set_languages("c11", "c++11")
if is_plat("windows") then
    set_languages("c++17")
end

-- option: warnings
option("warnings")
    set_default(false)
    set_showmenu(true)
    set_description("Enable or disable warnings")
option_end()

if has_config("warnings") then
    -- set warning everything
    set_warnings("everything")
    -- disable some compiler errors
    if is_plat("windows") then
        add_cxflags("/wd4514", "/wd4710", "/wd4711", "/wd5039", "/wd5045")
    end
    add_cflags("-Wno-declaration-after-statement")
    add_cxflags("-Wno-used-but-marked-unused")
    add_cxxflags("-Wno-c++98-compat-pedantic")
end

-- add build modes
add_rules("mode.check", "mode.debug", "mode.release")
if is_mode("check") and not is_plat("mingw") then
    local flags = {
        "-fsanitize=address,undefined",
        "-fsanitize-recover=address",
        "-fno-omit-frame-pointer",
        "-fsanitize=leak",
    }
    add_cxflags(flags)
    add_ldflags(flags)
end

target("a")
    -- make as a static/shared library
    set_kind("$(kind)")
    includes("check_cfuncs.lua")
    configvar_check_cfuncs("A_HAVE_HYPOT", "hypot", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_LOG1P", "log1p", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_FABS", "fabs", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_POW", "pow", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_EXP", "exp", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_LOG", "log", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_SIN", "sin", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_COS", "cos", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_TAN", "tan", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_ASIN", "asin", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_ACOS", "acos", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_ATAN", "atan", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_ATAN2", "atan2", {includes = "math.h"})
    configvar_check_cfuncs("A_HAVE_CSQRT", "csqrt", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CPOW", "cpow", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CEXP", "cexp", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CLOG", "clog", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CSIN", "csin", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CCOS", "ccos", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CTAN", "ctan", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CASIN", "casin", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CACOS", "cacos", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CATAN", "catan", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CSINH", "csinh", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CCOSH", "ccosh", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CTANH", "ctanh", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CASINH", "casinh", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CACOSH", "cacosh", {includes = "complex.h"})
    configvar_check_cfuncs("A_HAVE_CATANH", "catanh", {includes = "complex.h"})
    -- get xmake version
    on_load(function (target)
        import("lib.detect.find_programver")
        target:set("configvar", "XMAKE_VERSION", find_programver("xmake"))
    end)
    -- set the auto-generated a.config.h
    add_configfiles("xmake/config.h", {filename = "a.config.h"})
    -- set shared library symbols
    if is_kind("shared") then
        -- import symbols
        add_defines("A_SHARED", {interface = true})
        -- export symbols
        add_defines("A_EXPORTS")
    end
    -- add include directories
    add_includedirs("$(buildir)", {public = true})
    add_includedirs("include", {public = true})
    add_defines("A_CONFIG", {public = true})
    -- add the header files for installing
    add_headerfiles("$(buildir)/a.config.h")
    add_headerfiles("include/(**.hpp)")
    add_headerfiles("include/(**.h)")
    -- add the common source files
    add_files("src/**.c","src/**.cpp")
    -- add the platform options
    if not is_plat("windows", "mingw") then
        add_cxflags("-fPIC")
        add_syslinks("m")
    end
target_end()

-- include ffi sources
includes("ffi/lua")

-- option: with-rust
option("with-rust")
    set_default(false)
    set_showmenu(true)
    set_description("Enable or disable rust")
option_end()

if has_config("with-rust") then
    add_requires("cargo::liba", {configs = {cargo_toml = path.join(os.projectdir(), "Cargo.toml")}})
    target("a.rust")
        add_deps("a")
        set_basename("a")
        set_kind("static")
        add_files("src/lib.rs")
        add_packages("cargo::liba")
    target_end()
end

-- include test sources
includes("test")
