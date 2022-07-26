-- set project name
set_project("liba")

-- set xmake minimum version
set_xmakever("2.5.0")

-- set project version
set_version("0.1.0", {build = "%Y%m%d%H%M"})

-- set language: c11 c++17
set_languages("c11", "c++17")

-- set warning everything
set_warnings("everything")

-- disable some compiler errors
add_cxflags("-Wno-reserved-id-macro", "-Wno-reserved-identifier", "-Wno-used-but-marked-unused", "-Wno-reserved-macro-identifier")
add_cflags("-Wno-declaration-after-statement")
add_cxxflags("-Wno-c++98-compat-pedantic")

-- add build modes
add_rules("mode.debug", "mode.release")

target("a")

    -- make as a static/shared library
    set_kind("$(kind)")

    -- set the auto-generated a.config.h
    add_configfiles("xmake/config.h", {filename = "a.config.h"})
    set_configdir("$(curdir)/include")

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
        add_syslinks("m")
    end

    -- get xmake version
    on_load(function (target)
        import("lib.detect.find_programver")
        target:set("configvar", "XMAKE_VERSION", find_programver("xmake"))
    end)

target_end()

target("aa")

    -- add the dependent target
    add_deps("a")

    -- make as a static/shared library
    set_kind("$(kind)")

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
        add_syslinks("m")
    end

target_end()

-- include ffi sources
includes("ffi/lua")

-- option: with-rust
option("with-rust")
    set_default(false)
    set_showmenu(true)
    set_values(false, true)
    set_description("Enable or disable rust")
option_end()

if has_config("with-rust") then
    add_requires("cargo::liba", {configs = {cargo_toml = path.join(os.projectdir(), "Cargo.toml")}})
    target("a-rust")
        add_deps("a")
        set_basename("a")
        set_kind("$(kind)")
        add_files("src/**.rs")
        add_packages("cargo::liba")
    target_end()
end

-- include test sources
includes("test")
