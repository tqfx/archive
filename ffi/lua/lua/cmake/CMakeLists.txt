include(GNUInstallDirs)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE NO)
option(LUA_32BITS "build lua 32bits" OFF)

if(LUA_32BITS)
  set(LUA_32BITS 1 CACHE BOOL "" FORCE)
else()
  set(LUA_32BITS 0 CACHE BOOL "" FORCE)
endif()

if(DEFINED ENV{ANDROID_ROOT})
  list(APPEND CMAKE_PREFIX_PATH $ENV{ANDROID_ROOT})
endif()

if(DEFINED ENV{PREFIX})
  list(APPEND CMAKE_PREFIX_PATH $ENV{PREFIX})
endif()

find_library(READLINE_LIBRARY NAMES readline)
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
find_library(MATH_LIBRARY NAMES m DOC "lua math library")

if(READLINE_LIBRARY AND READLINE_INCLUDE_DIR)
  set(READLINE_FOUND TRUE)
else()
  set(READLINE_FOUND 0)
endif()

if(NOT WIN32)
  file(READ ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h LUACONF_H)
  string(REGEX REPLACE "([^/\\]+)$" "\\1/" LUA_ROOT "${CMAKE_INSTALL_PREFIX}")
  string(REGEX REPLACE "#define LUA_ROOT\t([^\n]+)\n" "#define LUA_ROOT\t\"${LUA_ROOT}\"\n" LUACONF_H "${LUACONF_H}")
  string(REGEX REPLACE "#define LUA_32BITS\t([^\n]+)\n" "#define LUA_32BITS\t${LUA_32BITS}\n" LUACONF_H "${LUACONF_H}")

  if(APPLE)
    if(LUA_VERSION VERSION_GREATER 5.1.5)
      set(LUA_CPATH_DEFAULT ".so;\" \\\\\n\tLUA_CDIR\"?.dylib;\" LUA_CDIR\"loadall.dylib;\" \"./?.dylib\"\n")
    else()
      set(LUA_CPATH_DEFAULT ".so;\" \\\\\n\t\"./?.dylib;\" LUA_CDIR\"?.dylib;\" LUA_CDIR\"loadall.dylib\"\n")
    endif()

    string(REGEX REPLACE "\.so\"\n" "${LUA_CPATH_DEFAULT}" LUACONF_H "${LUACONF_H}")
  endif()

  file(WRITE ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h "${LUACONF_H}")
endif()

if(DEFINED ENV{PREFIX})
  string(REGEX REPLACE "([^/\\]+)([/\\]*)$" "\\1/tmp/lua_XXXXXX" LUA_ROOT "$ENV{PREFIX}")
  file(READ ${CMAKE_CURRENT_LIST_DIR}/src/loslib.c LOSLIB_C)
  string(LENGTH "${LUA_ROOT}0" LUA_ROOT_LENGTH)
  string(REGEX REPLACE "#define LUA_TMPNAMTEMPLATE\t([^\n]+)\n" "#define LUA_TMPNAMTEMPLATE\t\"${LUA_ROOT}\"\n" LOSLIB_C "${LOSLIB_C}")
  string(REGEX REPLACE "#define LUA_TMPNAMBUFSIZE\t([^\n]+)\n" "#define LUA_TMPNAMBUFSIZE\t${LUA_ROOT_LENGTH}\n" LOSLIB_C "${LOSLIB_C}")
  file(WRITE ${CMAKE_CURRENT_LIST_DIR}/src/loslib.c "${LOSLIB_C}")
endif()

if(DEFINED ENV{ANDROID_ROOT})
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.13)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
endif()

if(LUA_VERSION VERSION_GREATER 5.3.6)
  set(DEFINE_SYMBOL LUA_COMPAT_5_3)
elseif(LUA_VERSION VERSION_GREATER 5.2.4)
  set(DEFINE_SYMBOL LUA_COMPAT_5_2)
else()
  set(DEFINE_SYMBOL LUA_COMPAT_ALL)
endif()

if(WIN32)
  set(LUA_PLATFORM LUA_BUILD_AS_DLL)
elseif(APPLE)
  set(LUA_PLATFORM LUA_USE_MACOSX)
elseif(UNIX)
  set(LUA_PLATFORM LUA_USE_LINUX)
else()
  set(LUA_PLATFORM LUA_USE_POSIX)
endif()

function(lua_library target)
  if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib AND CMAKE_C_COMPILER_ID MATCHES "TinyCC")
    set_target_properties(${target} PROPERTIES IMPORT_SUFFIX .def)
  endif()

  set_target_properties(${target} PROPERTIES OUTPUT_NAME lua
    POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL ${DEFINE_SYMBOL}
  )
  target_compile_definitions(${target} PUBLIC
    $<$<AND:$<BOOL:${READLINE_FOUND}>,$<VERSION_GREATER:${LUA_VERSION},5.3.6>>:LUA_USE_READLINE>
    $<$<BOOL:${LUA_PLATFORM}>:${LUA_PLATFORM}>
  )
  target_include_directories(${target} PUBLIC
    $<$<BOOL:${READLINE_FOUND}>:${READLINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${target} INTERFACE
    $<$<BOOL:${MATH_LIBRARY}>:${MATH_LIBRARY}>
  )
endfunction()

unset(SOURCES)
unset(SOURCES CACHE)
aux_source_directory(src SOURCES)
list(REMOVE_ITEM SOURCES src/lua.c)
list(REMOVE_ITEM SOURCES src/luac.c)

add_library(liblua SHARED ${SOURCES})
lua_library(liblua)
add_library(lualib STATIC $<TARGET_OBJECTS:liblua>)
lua_library(lualib)

add_executable(lua src/lua.c)
target_link_libraries(lua PRIVATE liblua)
add_executable(luac src/luac.c)
target_link_libraries(luac PRIVATE lualib)
target_link_libraries(liblua INTERFACE ${CMAKE_DL_LIBS}
  $<$<BOOL:${READLINE_FOUND}>:${READLINE_LIBRARY}>
)

if(WIN32)
  set(name lua${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR})
else()
  set(name lua${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
endif()

get_target_property(prop liblua INTERFACE_COMPILE_DEFINITIONS)
set(PROJECT_CFLAGS "$<$<BOOL:${prop}>:-D$<JOIN:${prop}, -D>>")
set_target_properties(liblua PROPERTIES OUTPUT_NAME ${name})
get_target_property(prop liblua INTERFACE_LINK_LIBRARIES)
set(PROJECT_LIBRARIES "-l$<JOIN:${name};${prop}, -l>")

file(GLOB_RECURSE PUBLIC_HEADER lua.h luaconf.h lualib.h lauxlib.h lua.hpp)
install(FILES ${PUBLIC_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS lualib liblua lua luac EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT ${PROJECT_NAME}-targets FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(FILES doc/lua.1 doc/luac.1 DESTINATION man/man1)
file(GENERATE
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  INPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.pc
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  @ONLY
)
include(CPack)
