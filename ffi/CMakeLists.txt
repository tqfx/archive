option(LIBA_LDOC "Enable or disable ffi ldoc" 0)
option(LIBA_LUA "Enable or disable ffi lua" 0)
option(WITH_LUA "Build with lua" 0)

if(LIBA_LUA OR WITH_LUA)
  set(A_LIBRARY a)

  if(NOT WITH_LUA)
    find_package(Lua)
  endif()

  if(LUA_FOUND)
    set(LUA_MATH_LIBRARY ${MATH_LIBRARY} CACHE STRING "" FORCE)
  else()
    add_subdirectory(lua/lua)
    set(LUA_EXECUTABLE ${CMAKE_CROSSCOMPILING_EMULATOR} ${LUA_EXECUTABLE})

    if(LIBA_SANITIZE)
      target_compile_sanitize(PUBLIC liblua lualib)
      target_link_sanitize(PUBLIC liblua lualib)
      set(A_LIBRARY asan)
    endif()
  endif()

  add_subdirectory(lua)
  set(A_LIBRARY a)
endif()

option(LIBA_JAVADOC "Enable or disable ffi javadoc" 0)
option(LIBA_JAVA "Enable or disable ffi java" 0)

if(LIBA_JAVA)
  find_package(Java)
  find_package(JNI)
endif()

if(Java_FOUND)
  add_subdirectory(java)
endif()

if(PYTHONINTERP_FOUND)
  add_subdirectory(python)
endif()

if(EMSCRIPTEN)
  option(LIBA_JAVASCRIPT "Enable or disable ffi javascript" 1)
else()
  option(LIBA_JAVASCRIPT "Enable or disable ffi javascript" 0)
endif()

if(LIBA_JAVASCRIPT)
  find_program(EMCC emcc)
  find_program(EMCXX em++)
  mark_as_advanced(EMCC EMCXX)

  if(EMCC AND EMCXX)
    find_program(NODE_EXECUTABLE node)
    mark_as_advanced(NODE_EXECUTABLE)
    add_subdirectory(javascript)
  endif()
endif()

option(LIBA_SWIG "Enable or disable ffi swig" 0)

if(LIBA_SWIG)
  # https://cmake.org/cmake/help/latest/module/UseSWIG.html
  if(POLICY CMP0078) # 3.13
    cmake_policy(SET CMP0078 NEW)
  endif() # UseSWIG_TARGET_NAME_PREFERENCE

  if(POLICY CMP0086) # 3.14
    cmake_policy(SET CMP0086 NEW)
  endif() # SWIG_MODULE_NAME

  find_package(SWIG)
endif()

if(SWIG_FOUND)
  include(UseSWIG)
  add_subdirectory(swig)
endif()
