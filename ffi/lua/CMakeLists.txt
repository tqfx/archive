set(LUA_MATH_LIBRARY ${LIBA_MATH} CACHE STRING "lua math library")
set(OBJECTS $<TARGET_OBJECTS:a>)

if(NOT WITH_LUA AND LIBA_LUA)
  find_package(Lua OPTIONAL_COMPONENTS lua)
endif()

if(NOT WITH_LUA AND(NOT LUA_FOUND OR LIBA_LUAJIT))
  find_package(LuaJIT OPTIONAL_COMPONENTS luajit)
  set(LUA_INCLUDE_DIR ${LUAJIT_INCLUDE_DIR})
  set(LUA_EXECUTABLE ${LUAJIT_EXECUTABLE})
  set(LUA_LIBRARIES ${LUAJIT_LIBRARIES})
endif()

if(NOT LUA_FOUND AND NOT LUAJIT_FOUND)
  add_subdirectory(lua)
  set(LUA_LIBRARIES liblua)
  set(LUA_EXECUTABLE ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:lua>)
  set(LUA_INCLUDE_DIR $<TARGET_PROPERTY:liblua,INTERFACE_INCLUDE_DIRECTORIES>)
  string(REGEX REPLACE "^([0-9]).*" "\\1" LUA_VERSION_MAJOR "${LUA_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_MINOR "${LUA_VERSION}")

  if(LIBA_SANITIZE)
    target_compile_sanitize(PUBLIC luaobj lualib liblua)
    target_link_sanitize(PUBLIC lualib liblua)
    set(OBJECTS $<TARGET_OBJECTS:asan>)
  endif()
endif()

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX lib)
else()
  set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
endif()

file_scaner(SOURCES RECURSE src)
add_library(alua SHARED ${SOURCES} ${OBJECTS})
set_target_properties(alua PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_compile_definitions(alua PRIVATE $<TARGET_PROPERTY:a,COMPILE_DEFINITIONS>)
target_include_directories(alua PRIVATE $<TARGET_PROPERTY:a,INCLUDE_DIRECTORIES>)
target_include_directories(alua PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(alua PRIVATE ${LUA_LIBRARIES})
set_library_options(alua)

install(TARGETS alua
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
)

if(PROJECT_IS_TOP_LEVEL)
  find_package(StyLua)
  find_package(LuaFormat)
  file(GLOB_RECURSE SOURCES test/*.lua)
endif()

if(STYLUA_FOUND)
  add_stylua(astylua VERBOSE ${SOURCES})
endif()

if(LUA_FORMAT_FOUND)
  add_lua_format(aluaformat VERBOSE ${SOURCES})
endif()

option(LIBA_LDOC "Enable/Disable ffi ldoc" 0)

if(LIBA_LDOC)
  find_package(LDoc)
endif()

if(LIBA_LDOC AND LDOC_FOUND)
  create_ldoc(aldoc
    CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/ldoc/config.ld
    OPTIONS -f markdown ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
endif()

if(LUA_EXECUTABLE)
  add_subdirectory(test)
endif()
