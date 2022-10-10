set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_library(MATH_LIBRARY NAMES m)
option(LUA_32BITS "lua 32bits" OFF)
find_library(READLINE_LIBRARY NAMES readline)
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)

if(NOT MATH_LIBRARY AND ANDROID)
  set(MATH_LIBRARY m CACHE STRING "math library" FORCE)
endif()

if(LUA_32BITS)
  set(LUA_32BITS 1 CACHE BOOL "lua 32bits" FORCE)
else()
  set(LUA_32BITS 0 CACHE BOOL "lua 32bits" FORCE)
endif()

file(READ ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h LUACONF)
set(LUA_ROOT ${CMAKE_INSTALL_PREFIX} CACHE STRING "lua root")
string(REGEX REPLACE "([^/\\]+)$" "\\1/" LUA_ROOT "${LUA_ROOT}")
string(REGEX REPLACE "#define LUA_ROOT\t([^\n]+)\n" "#define LUA_ROOT\t\"${LUA_ROOT}\"\n" LUACONF "${LUACONF}")
string(REGEX REPLACE "#define LUA_32BITS\t([^\n]+)\n" "#define LUA_32BITS\t${LUA_32BITS}\n" LUACONF "${LUACONF}")
file(WRITE ${CMAKE_CURRENT_LIST_DIR}/src/luaconf.h "${LUACONF}")

if(ANDROID)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.13)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
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
  target_compile_definitions(${target} PRIVATE
    $<$<BOOL:${READLINE_INCLUDE_DIR}>:LUA_USE_READLINE>
    $<$<BOOL:${LUA_PLATFORM}>:${LUA_PLATFORM}>
  )
  target_include_directories(${target} PUBLIC
    $<$<BOOL:${READLINE_INCLUDE_DIR}>:${READLINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${target} INTERFACE
    $<$<BOOL:${MATH_LIBRARY}>:${MATH_LIBRARY}>
  )
  set_target_properties(${target} PROPERTIES
    OUTPUT_NAME lua DEFINE_SYMBOL LUA_COMPAT_5_3
  )
endfunction()

unset(SOURCES)
unset(SOURCES CACHE)
include(GNUInstallDirs)
aux_source_directory(src SOURCES)
list(REMOVE_ITEM SOURCES src/lua.c)
list(REMOVE_ITEM SOURCES src/luac.c)

add_library(lua-shared SHARED ${SOURCES})
lua_library(lua-shared)
add_library(lua-static STATIC $<TARGET_OBJECTS:lua-shared>)
lua_library(lua-static)
target_link_libraries(lua-shared INTERFACE ${CMAKE_DL_LIBS}
  $<$<BOOL:${READLINE_LIBRARY}>:${READLINE_LIBRARY}>
)

if(WIN32)
  set_target_properties(lua-shared PROPERTIES
    OUTPUT_NAME lua${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR}
  )
endif()

add_executable(lua src/lua.c)
target_link_libraries(lua PRIVATE lua-shared)
add_executable(luac src/luac.c)
target_link_libraries(luac PRIVATE lua-static)

install(FILES src/lua.h src/luaconf.h src/lualib.h src/lauxlib.h src/lua.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(TARGETS lua luac lua-static lua-shared EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT ${PROJECT_NAME}-targets FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(FILES doc/lua.1 doc/luac.1 DESTINATION man/man1)
include(InstallRequiredSystemLibraries)
include(CPack)
