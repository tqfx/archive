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
