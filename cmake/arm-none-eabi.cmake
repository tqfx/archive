set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(TOOLCHAIN_PREFIX arm-none-eabi)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(CMAKE_AR ${TOOLCHAIN_PREFIX}-gcc-ar)
find_program(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
find_program(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
find_program(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}-gcc-ranlib)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER} -x assembler-with-cpp)

find_program(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)
find_program(CMAKE_DEBUGER ${TOOLCHAIN_PREFIX}-gdb)
find_program(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
find_program(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}-objdump)
find_program(CMAKE_CPPFILT ${TOOLCHAIN_PREFIX}-c++filt)
find_program(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}-gcc NO_CACHE)
get_filename_component(CMAKE_FIND_ROOT_PATH "${CMAKE_FIND_ROOT_PATH}" DIRECTORY)
get_filename_component(CMAKE_FIND_ROOT_PATH "${CMAKE_FIND_ROOT_PATH}" DIRECTORY)
set(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
