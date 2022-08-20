-- option: with-lua
option("with-lua")
    set_default(false)
    set_showmenu(true)
    set_values(false, true)
    set_description("Enable or disable lua")
option_end()

if has_config("with-lua") then
    add_requires("lua")
    target("a-lua")
        set_basename("a")
        add_deps("a.objs")
        add_packages("lua")
        add_rules("swig.c", {moduletype = "lua"})
        add_files("src/**.c", {swigflags = "-no-old-metatable-bindings"})
        add_defines("A_EXPORTS")
        on_load(function (target)
            target:set("targetdir", path.join(target:targetdir(), "lua"))
            target:set("prefixname", "lib")
            if target:is_plat("windows", "mingw") then
                target:set("extension", ".dll")
            end
        end)
    target_end()
end
