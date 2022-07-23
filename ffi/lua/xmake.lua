option("with_lua")
    set_showmenu(true)
    set_values(false, true)
option_end()

if has_config("with_lua") then
    add_requires("lua")
    target("lua-a")
        set_group("liba")
        set_basename("a")
        add_rules("swig.c", {moduletype = "lua"})
        add_files("src/**.c", {swigflags = "-no-old-metatable-bindings"})
        add_defines("A_EXPORTS")
        add_packages("lua")
        add_deps("a")
        on_load(function (target)
            target:set("prefixname", "lib")
            target:set("targetdir", path.join(target:targetdir(), "lua"))
            if target:is_plat("windows", "mingw") then
                target:set("extension", ".dll")
            end
        end)
    target_end()
end
