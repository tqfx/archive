-- set project name
set_project("liba")

-- set xmake minimum version
set_xmakever("2.5.0")

-- set project version
set_version("0.1.0", {build = "%Y%m%d%H%M"})

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
    add_cxflags("-Wno-reserved-identifier", "-Wno-used-but-marked-unused")
    add_cflags("-Wno-declaration-after-statement")
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

target("ac.objs")
    -- make as a collection of objects
    set_kind("object")
    -- get xmake version
    on_load(function (target)
        import("lib.detect.find_programver")
        target:set("configvar", "XMAKE_VERSION", find_programver("xmake"))
    end)
    -- set the auto-generated a.config.h
    add_configfiles("xmake/config.h", {filename = "a.config.h"})
    set_configdir("$(curdir)/include")
    -- set shared library symbols
    if is_kind("shared") then
        -- export symbols
        add_defines("A_EXPORTS")
        -- import symbols
        add_defines("A_SHARED", {interface = true})
    end
    -- add include directories
    add_includedirs("include", {public = true})
    -- add the header files for installing
    add_headerfiles("include/(**.h)")
    -- add the common source files
    add_files("src/**.c")
    -- add the platform options
    if not is_plat("windows", "mingw") then
        add_cxflags("-fPIC")
        add_syslinks("m")
    end
target_end()

target("ac")
    -- make as a static/shared library
    set_kind("$(kind)")
    -- add the dependent target
    add_deps("ac.objs")
target_end()

target("ax.objs")
    -- make as a a collection of objects
    set_kind("object")
    -- set shared library symbols
    if is_kind("shared") then
        -- export symbols
        add_defines("A_EXPORTS")
        -- import symbols
        add_defines("A_SHARED", {interface = true})
    end
    -- add include directories
    add_includedirs("include", {public = true})
    -- add the header files for installing
    add_headerfiles("include/(**.hpp)")
    -- add the common source files
    add_files("src/**.cpp")
    -- add the platform options
    if not is_plat("windows", "mingw") then
        add_cxflags("-fPIC")
        add_syslinks("m")
    end
target_end()

target("ax")
    -- make as a static/shared library
    set_kind("$(kind)")
    -- add the dependent target
    add_deps("ax.objs")
target_end()

target("a.objs")
    -- make as a a collection of objects
    set_kind("object")
    -- add the dependent target
    add_deps("ac.objs", "ax.objs")
target_end()

target("a")
    -- make as a static/shared library
    set_kind("$(kind)")
    -- add the dependent target
    add_deps("a.objs")
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
