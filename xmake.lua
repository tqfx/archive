add_rules("mode.debug", "mode.release")

set_project("liba")
set_license("MPL-2.0")
set_version("0.1.0", {build = "%Y%m%d%H%M"})
set_description("An algorithm library based on C/C++ language")

target()
    set_group("liba")
    set_languages("c11", "c++17")
    set_warnings("everything")
    on_load(function (target)
        local flags = {
            "-Wno-reserved-id-macro",
            "-Wno-reserved-identifier",
            "-Wno-used-but-marked-unused",
            "-Wno-reserved-macro-identifier",
        }
        target:add("cflags", flags, "-Wno-declaration-after-statement")
        target:add("cxxflags", flags, "-Wno-c++98-compat-pedantic")
    end)
target_end()

target("a")
    set_group("liba")
    set_kind("$(kind)")
    add_files("src/**.c")
    add_includedirs("include", {public = true})
    set_configdir("$(curdir)/src")
    add_configfiles("xmake/config.h")
    add_defines("A_CONFIG")
    if is_kind("shared") then
        add_defines("A_EXPORTS")
        add_defines("A_SHARED", {interface = true})
    end
    if not is_plat("windows", "mingw") then
        add_syslinks("m")
    end
target_end()

target("aa")
    set_group("liba")
    set_kind("$(kind)")
    add_files("src/**.cpp")
    add_includedirs("include", {public = true})
    set_configdir("$(curdir)/src")
    add_configfiles("xmake/config.hpp")
    add_defines("A_CONFIG")
    if is_kind("shared") then
        add_defines("A_EXPORTS")
        add_defines("A_SHARED", {interface = true})
    end
    if not is_plat("windows", "mingw") then
        add_syslinks("m")
    end
target_end()

includes("ffi/lua")

option("with-rust")
    set_showmenu(true)
    set_values(false, true)
option_end()

if has_config("with-rust") then
    add_requires("cargo::liba", {configs = {cargo_toml = path.join(os.projectdir(), "Cargo.toml")}})
    target("rust-c")
        set_group("liba")
        set_basename("a")
        set_kind("$(kind)")
        add_files("src/**.rs")
        add_packages("cargo::liba")
        add_deps("a")
    target_end()
end
