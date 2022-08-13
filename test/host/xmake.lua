target("test-str")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("str.cc")
    add_deps("a")
target_end()

target("test-vec")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("vec.cc")
    add_deps("a")
target_end()

target("test-vector")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("vector.cc")
    add_deps("a")
target_end()

target("test-vectors")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("vectors.cc")
    add_deps("a")
target_end()

target("test-que")
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files("que.cc")
    add_deps("a")
target_end()
