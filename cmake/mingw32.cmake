set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX i686-w64-mingw32)

find_program(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
find_program(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
find_program(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}-gcc-ranlib)
find_program(CMAKE_AR ${TOOLCHAIN_PREFIX}-gcc-ar)

get_filename_component(TOOLCHAIN_PATH "${CMAKE_C_COMPILER}" DIRECTORY)
get_filename_component(TOOLCHAIN_PATH "${TOOLCHAIN_PATH}" DIRECTORY)

set(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}")

if(NOT WIN32)
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif()

if(UNIX)
  find_program(TARGET_SYSTEM_EMULATOR wine)

  if(NOT TARGET_SYSTEM_EMULATOR)
    unset(TARGET_SYSTEM_EMULATOR)
  endif()
endif()
