find_program(ZIG_EXECUTABLE zig REQUIRED DOC "Zig compiler")
set(CMAKE_CXX_COMPILER ${ZIG_EXECUTABLE} c++)
set(CMAKE_C_COMPILER ${ZIG_EXECUTABLE} cc)
mark_as_advanced(ZIG_EXECUTABLE)
