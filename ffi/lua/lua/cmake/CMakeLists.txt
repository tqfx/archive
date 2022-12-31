include(GNUInstallDirs)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS 1)
set(CMAKE_C_STANDARD_REQUIRED 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_POSITION_INDEPENDENT_CODE 0)
option(LUA_32BITS "build lua 32bits" 0)

if(WIN32)
  option(LUA_READLINE "Enable or disable readline" 0)
else()
  option(LUA_READLINE "Enable or disable readline" 1)
endif()

if(LUA_READLINE)
  find_package(ReadLine)
endif()

if(LUA_32BITS)
  set(LUA_32BITS 1 CACHE BOOL "build lua 32bits" FORCE)
else()
  set(LUA_32BITS 0 CACHE BOOL "build lua 32bits" FORCE)
endif()

if(NOT LUA_MATH_LIBRARY AND WIN32)
  unset(LUA_MATH_LIBRARY CACHE)
elseif(NOT LUA_MATH)
  set(LUA_MATH_LIBRARY m)
endif()

if(NOT WIN32 AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h)
  file(READ ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h luaconf_h)
  string(REGEX REPLACE "([^/\\]+)$" "\\1/" LUA_ROOT "${CMAKE_INSTALL_PREFIX}")
  string(REGEX REPLACE "#define LUA_USE_READLINE([^\n]+)\n" "" luaconf_h "${luaconf_h}")
  string(REGEX REPLACE "#define LUA_ROOT\t([^\n]+)\n" "#define LUA_ROOT\t\"${LUA_ROOT}\"\n" luaconf_h "${luaconf_h}")
  string(REGEX REPLACE "#define LUA_32BITS\t([^\n]+)\n" "#define LUA_32BITS\t${LUA_32BITS}\n" luaconf_h "${luaconf_h}")

  if(APPLE)
    if(LUA_VERSION VERSION_GREATER_EQUAL 5.2)
      set(LUA_CPATH_DEFAULT ".so;\" \\\\\n\tLUA_CDIR\"?.dylib;\" LUA_CDIR\"loadall.dylib;\" \"./?.dylib\"\n")
    else()
      set(LUA_CPATH_DEFAULT ".so;\" \\\\\n\t\"./?.dylib;\" LUA_CDIR\"?.dylib;\" LUA_CDIR\"loadall.dylib\"\n")
    endif()

    string(REGEX REPLACE "\.so\"\n" "${LUA_CPATH_DEFAULT}" luaconf_h "${luaconf_h}")
  endif()

  file(WRITE ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h "${luaconf_h}")
  unset(luaconf_h)
endif()

if(DEFINED ENV{PREFIX} AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/src/loslib.c)
  string(REGEX REPLACE "([^/\\]+)([/\\]*)$" "\\1/tmp/lua_XXXXXX" LUA_ROOT "$ENV{PREFIX}")
  file(READ ${CMAKE_CURRENT_LIST_DIR}/src/loslib.c loslib_c)
  string(LENGTH "${LUA_ROOT}0" LUA_ROOT_LENGTH)
  string(REGEX REPLACE "#define LUA_TMPNAMTEMPLATE\t([^\n]+)\n" "#define LUA_TMPNAMTEMPLATE\t\"${LUA_ROOT}\"\n" loslib_c "${loslib_c}")
  string(REGEX REPLACE "#define LUA_TMPNAMBUFSIZE\t([^\n]+)\n" "#define LUA_TMPNAMBUFSIZE\t${LUA_ROOT_LENGTH}\n" loslib_c "${loslib_c}")
  file(WRITE ${CMAKE_CURRENT_LIST_DIR}/src/loslib.c "${loslib_c}")
  unset(loslib_c)
endif()

if(DEFINED ENV{ANDROID_ROOT} AND EXISTS $ENV{ANDROID_ROOT})
  set(CMAKE_POSITION_INDEPENDENT_CODE 1)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.13)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
endif()

if(LUA_VERSION VERSION_GREATER_EQUAL 5.4)
  set(LUA_COMPAT LUA_COMPAT_5_3)
elseif(LUA_VERSION VERSION_GREATER_EQUAL 5.3)
  set(LUA_COMPAT LUA_COMPAT_5_2)
else()
  set(LUA_COMPAT LUA_COMPAT_ALL)
endif()

if(APPLE)
  set(LUA_PLATFORM LUA_USE_MACOSX)
elseif(UNIX)
  set(LUA_PLATFORM LUA_USE_LINUX)
elseif(NOT WIN32)
  set(LUA_PLATFORM LUA_USE_POSIX)
endif()

function(lua_library target)
  if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib AND CMAKE_C_COMPILER_ID MATCHES "TinyCC")
    set_target_properties(${target} PROPERTIES IMPORT_SUFFIX .def)
  endif()

  set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${LUA_COMPAT})
  target_link_libraries(${target} INTERFACE ${CMAKE_DL_LIBS} ${LUA_MATH_LIBRARY})
  target_compile_definitions(${target} PUBLIC ${LUA_COMPAT} ${LUA_PLATFORM})
  target_include_directories(${target} PUBLIC $<INSTALL_INTERFACE:include>)
endfunction()

set(SOURCES "")
aux_source_directory(src SOURCES)
list(REMOVE_ITEM SOURCES src/lua.c)
list(REMOVE_ITEM SOURCES src/luac.c)
add_library(liblua SHARED ${SOURCES})
lua_library(liblua)
add_library(lualib STATIC $<TARGET_OBJECTS:liblua>)
lua_library(lualib)
add_executable(lua src/lua.c)
add_executable(luac src/luac.c)
target_link_libraries(luac PRIVATE lualib)

if(BUILD_SHARED_LIBS)
  target_link_libraries(lua PRIVATE liblua)
else()
  target_link_libraries(lua PRIVATE lualib)
endif()

if(BUILD_SHARED_LIBS AND WIN32)
  target_compile_definitions(liblua PUBLIC LUA_BUILD_AS_DLL)
endif()

if(LUA_READLINE AND READLINE_FOUND)
  target_compile_definitions(lua PRIVATE LUA_USE_READLINE)
  target_link_libraries(lua PRIVATE ReadLine::readline)
endif()

set(static lua${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(shared lua${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR})
set_target_properties(lualib PROPERTIES OUTPUT_NAME ${static})

if(WIN32)
  set_target_properties(liblua PROPERTIES OUTPUT_NAME ${shared})
else()
  set_target_properties(liblua PROPERTIES OUTPUT_NAME ${static})
endif()

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

get_property(prop TARGET liblua PROPERTY INTERFACE_COMPILE_DEFINITIONS)
set(PC_CFLAGS "-D$<JOIN:${prop}, -D>")
get_property(prop TARGET liblua PROPERTY INTERFACE_LINK_LIBRARIES)
set(PC_LDFLAGS "-l${static}")

if(prop)
  set(PC_STATIC_LDFLAGS "-l$<JOIN:${prop}, -l>")
endif()

file(GENERATE
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${static}.pc
  INPUT ${CMAKE_CURRENT_BINARY_DIR}/${static}.pc
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${static}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.pc
  ${CMAKE_CURRENT_BINARY_DIR}/${static}.pc
  @ONLY
)

include(CPack)
