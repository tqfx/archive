-- option: with-lua
option("with-lua")
    set_showmenu(true)
    set_values("lua", "luajit")
    set_description("Enable/Disable lua")
option_end()

if has_config("with-lua") then
    add_requires(get_config("with-lua"))
    target("a.lua")
        set_basename("a")
        set_kind("shared")
        add_deps("a.objs")
        add_files("src/**.c")
        set_prefixname("lib")
        add_packages(get_config("with-lua"))
        if is_plat("windows", "mingw") then
            set_extension(".dll")
        end
        add_defines("A_EXPORTS")
        on_load(function (target)
            local subdir = get_config("with-lua")
            local libdir = path.join("lib", subdir)
            target:set("targetdir", path.join(target:targetdir(), subdir))
            target:set("installfiles", target:targetfile(), {prefixdir = libdir})
        end)
    target_end()
end
