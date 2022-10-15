option(ENABLE_LDOC "Enable ffi lua documentation" OFF)
option(ENABLE_LUA "Enable ffi lua" OFF)
option(WITH_LUA "Build with lua" OFF)

if(ENABLE_LUA)
  if(NOT WITH_LUA)
    find_package(Lua)
  endif()

  if(LUA_FOUND)
    if(NOT LUA_MATH_LIBRARY AND ANDROID)
      set(LUA_MATH_LIBRARY m CACHE STRING "lua link math library" FORCE)
    endif()
  else()
    add_subdirectory(lua/cmake)
    target_compile_sanitize(PUBLIC ${LUA_LIBRARIES})
    target_link_sanitize(PUBLIC ${LUA_LIBRARIES} lualib)
  endif()

  add_subdirectory(lua)
endif()

option(ENABLE_JAVA "Enable ffi java" OFF)
option(ENABLE_JAVADOC "Enable ffi java documentation" OFF)

if(ENABLE_JAVA)
  find_package(Java)
  find_package(JNI)
endif()

if(Java_FOUND)
  add_subdirectory(java)
endif()

if(PYTHONINTERP_FOUND)
  add_subdirectory(python)
endif()

option(ENABLE_JAVASCRIPT "Enable ffi javascript" OFF)

if(ENABLE_JAVASCRIPT)
  find_program(EMCC emcc)
  find_program(EMCXX em++)

  if(EMCC AND EMCXX)
    find_program(NODE_EXECUTABLE node)
    add_subdirectory(javascript)
  endif()
endif()

option(ENABLE_SWIG "Enable ffi swig" OFF)

if(ENABLE_SWIG)
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
