-- option: with-lua
option("with-lua")
    set_default(false)
    set_showmenu(true)
    set_description("Enable/Disable lua")
option_end()

if has_config("with-lua") then
    if has_config("warning") then
        add_cxflags("-Wno-documentation", "-Wno-documentation-unknown-command")
    end
    add_requires("lua")
    target("a.lua")
        set_basename("a")
        set_kind("shared")
        add_deps("a.objs")
        add_packages("lua")
        add_files("src/**.c")
        set_prefixname("lib")
        if is_plat("windows", "mingw") then
            set_extension(".dll")
        end
        add_defines("A_EXPORTS")
        on_load(function (target)
            target:set("targetdir", path.join(target:targetdir(), "lua"))
            target:set("installfiles", target:targetfile(), {prefixdir = "lib/lua/5.4"})
        end)
    target_end()
end
