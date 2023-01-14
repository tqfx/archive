remove_files = remove_files or del_files

function building(sources)
    set_group("test")
    set_default(false)
    set_kind("binary")
    add_files(sources)
    if has_config("with-cxx") then
        add_defines("HAS_CXX")
    else
        remove_files("*.cpp")
    end
    add_deps("a")
end

target("test.a")
    building({"lib.c", "lib.cpp"})
target_end()

target("test.main")
    building({"main.c", "main.cpp"})
target_end()

target("test.math")
    building({"math.c", "math.cpp"})
target_end()

target("test.version")
    building({"version.c", "version.cpp"})
target_end()

target("test.arr")
    building({"arr.c", "arr.cpp"})
target_end()

target("test.crc")
    building({"crc.c", "crc.cpp"})
target_end()

target("test.list")
    building({"list.c", "list.cpp"})
target_end()

target("test.slist")
    building({"slist.c", "slist.cpp"})
target_end()

target("test.complex")
    building({"complex.c", "complex.cpp"})
target_end()

target("test.pid")
    building({"pid.c", "pid.cpp"})
target_end()

target("test.fpid")
    building({"fpid.c", "fpid.cpp"})
target_end()

target("test.poly")
    building({"poly.c", "poly.cpp"})
target_end()

target("test.polytrack")
    building({"polytrack.c", "polytrack.cpp"})
target_end()

target("test.notefreqs")
    building({"notefreqs.c", "notefreqs.cpp"})
target_end()

target("test.operator")
    building({"operator.c", "operator.cpp"})
target_end()

includes("host")
