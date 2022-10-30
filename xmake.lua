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

target("a.objs")
    -- make as a collection of objects
    set_kind("object")
    -- custom load target configuration
    on_load(function (target)
        import("core.project.config")
        import("lib.detect.find_library")
        import("lib.detect.find_programver")
        target:set("configvar", "XMAKE_VERSION", find_programver("xmake"))
        local m = {}
        if config.get("plat") == 'mingw' then
            table.insert(m, "/usr/" .. config.get("arch") .. "-w64-mingw32/lib")
        end
        if config.get("plat") == 'linux' then
            table.insert(m, "/usr/lib/" .. config.get("arch") .. "-linux-gnu")
            table.insert(m, "/lib/" .. config.get("arch") .. "-linux-gnu")
        end
        if string.find(config.get("arch"), "64") then
            table.insert(m, "/system/lib64")
            table.insert(m, "/usr/lib64")
            table.insert(m, "/lib64")
        else
            table.insert(m, "/system/lib32")
            table.insert(m, "/usr/lib32")
            table.insert(m, "/lib32")
        end
        table.insert(m, "/system/lib")
        table.insert(m, "/usr/lib")
        table.insert(m, "/lib")
        local m = find_library("m", m)
        if m then
            target:add("linkdirs", m.linkdir, {public = true})
            target:add("links", m.link, {public = true})
        end
    end)
    -- detect c code functions
    includes("check_cfuncs.lua")
    local math = {includes = "math.h"}
    configvar_check_cfuncs("A_HAVE_HYPOT", "hypot", math)
    configvar_check_cfuncs("A_HAVE_LOG1P", "log1p", math)
    configvar_check_cfuncs("A_HAVE_FABS", "fabs", math)
    configvar_check_cfuncs("A_HAVE_POW", "pow", math)
    configvar_check_cfuncs("A_HAVE_EXP", "exp", math)
    configvar_check_cfuncs("A_HAVE_LOG", "log", math)
    configvar_check_cfuncs("A_HAVE_SIN", "sin", math)
    configvar_check_cfuncs("A_HAVE_COS", "cos", math)
    configvar_check_cfuncs("A_HAVE_TAN", "tan", math)
    configvar_check_cfuncs("A_HAVE_ASIN", "asin", math)
    configvar_check_cfuncs("A_HAVE_ACOS", "acos", math)
    configvar_check_cfuncs("A_HAVE_ATAN", "atan", math)
    configvar_check_cfuncs("A_HAVE_ATAN2", "atan2", math)
    local complex = {includes = "complex.h"}
    configvar_check_cfuncs("A_HAVE_CSQRT", "csqrt", complex)
    configvar_check_cfuncs("A_HAVE_CPOW", "cpow", complex)
    configvar_check_cfuncs("A_HAVE_CEXP", "cexp", complex)
    configvar_check_cfuncs("A_HAVE_CLOG", "clog", complex)
    configvar_check_cfuncs("A_HAVE_CSIN", "csin", complex)
    configvar_check_cfuncs("A_HAVE_CCOS", "ccos", complex)
    configvar_check_cfuncs("A_HAVE_CTAN", "ctan", complex)
    configvar_check_cfuncs("A_HAVE_CASIN", "casin", complex)
    configvar_check_cfuncs("A_HAVE_CACOS", "cacos", complex)
    configvar_check_cfuncs("A_HAVE_CATAN", "catan", complex)
    configvar_check_cfuncs("A_HAVE_CSINH", "csinh", complex)
    configvar_check_cfuncs("A_HAVE_CCOSH", "ccosh", complex)
    configvar_check_cfuncs("A_HAVE_CTANH", "ctanh", complex)
    configvar_check_cfuncs("A_HAVE_CASINH", "casinh", complex)
    configvar_check_cfuncs("A_HAVE_CACOSH", "cacosh", complex)
    configvar_check_cfuncs("A_HAVE_CATANH", "catanh", complex)
    -- set the auto-generated a.config.h
    add_configfiles("xmake/config.h", {filename = "a.config.h"})
    add_defines("A_CONFIG", {public = true})
    -- set export library symbols
    add_defines("A_EXPORTS")
    -- add include directories
    add_includedirs("$(buildir)", {public = true})
    add_includedirs("include", {public = true})
    -- add the header files for installing
    add_headerfiles("$(buildir)/a.config.h")
    add_headerfiles("include/(**.hpp)")
    add_headerfiles("include/(**.h)")
    -- add the common source files
    add_files("src/**.c", "src/**.cpp")
    -- add the platform options
    if not is_plat("windows", "mingw") then
        add_cxflags("-fPIC")
    end
target_end()

target("a")
    -- make as a static/shared library
    set_kind("static")
    -- add the dependent target
    add_deps("a.objs")
target_end()

target("liba")
    set_basename("a")
    set_prefixname("lib")
    -- make as a shared library
    set_kind("shared")
    -- add the dependent target
    add_deps("a.objs")
    -- add the platform options
    if is_plat("windows") then
        add_defines("A_IMPORTS", {interface = true})
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
        set_basename("a")
        set_kind("static")
        add_deps("a.objs")
        add_files("src/lib.rs")
        add_packages("cargo::liba")
    target_end()
end

-- include test sources
includes("test")
