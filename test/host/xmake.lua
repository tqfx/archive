target("test.str")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("str.c", "str.cpp")
    add_deps("a")
target_end()

target("test.vec")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("vec.c", "vec.cpp")
    add_deps("a")
target_end()

target("test.que")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("que.c", "que.cpp")
    add_deps("a")
target_end()

target("test.vector")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("vector.c", "vector.cpp")
    add_deps("a")
target_end()
