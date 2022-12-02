option(ENABLE_LDOC "Enable ffi lua documentation" OFF)
option(ENABLE_LUA "Enable ffi lua" OFF)
option(WITH_LUA "Build with lua" OFF)
set(A_LIBRARY a)

if(ENABLE_LUA OR WITH_LUA)
  if(NOT WITH_LUA)
    find_package(Lua)
  endif()

  if(LUA_FOUND)
    set(LUA_MATH_LIBRARY ${MATH_LIBRARY} CACHE STRING "" FORCE)
  else()
    add_subdirectory(lua/lua)
    set(LUA_EXECUTABLE ${TARGET_SYSTEM_EMULATOR} ${LUA_EXECUTABLE})

    if(ENABLE_SANITIZE)
      target_link_sanitize(PUBLIC ${LUA_LIBRARIES} lualib)
      target_compile_sanitize(PUBLIC ${LUA_LIBRARIES})
      set(A_LIBRARY asan)
    endif()
  endif()

  add_subdirectory(lua)
  unset(A_LIBRARY)
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
  mark_as_advanced(EMCC EMCXX)

  if(EMCC AND EMCXX)
    find_program(NODE_EXECUTABLE node)
    mark_as_advanced(NODE_EXECUTABLE)
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
