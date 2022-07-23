target("test-a")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("test.c")
    add_deps("a")
target_end()

target("test-a+")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("test.cc")
    add_deps("a")
target_end()

target("test-a++")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("test.cpp")
    add_deps("aa")
target_end()

target("test-math")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("math.c")
    add_deps("a")
target_end()

target("test-real")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("real.c")
    add_deps("a")
target_end()

target("test-list")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("list.c")
    add_deps("a")
target_end()

target("test-slist")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("slist.c")
    add_deps("a")
target_end()

target("test-operator")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("operator.c")
    add_deps("a")
target_end()

includes("misc")
includes("host")
