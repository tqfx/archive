if(NOT PROJECT_IS_TOP_LEVEL)
  set(BUILD_TESTING 0)
endif()

if(NOT CMAKE_FIND_LIBRARY_PREFIXES)
  set(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
endif()

option(LIBA_LUA "Enable/Disable ffi lua" 0)
option(LIBA_LUAJIT "Enable/Disable ffi luajit" 0)
option(WITH_LUA "Enable/Disable build with lua" 0)

if(WITH_LUA OR LIBA_LUA OR LIBA_LUAJIT)
  add_subdirectory(lua)
endif()

option(LIBA_JAVA "Enable/Disable ffi java" 0)

if(LIBA_JAVA)
  find_package(Java)
  find_package(JNI)
endif()

if(LIBA_JAVA AND Java_FOUND)
  add_subdirectory(java)
endif()

if(LIBA_PYTHON AND PYTHON_FOUND)
  add_subdirectory(python)
endif()

if(EMSCRIPTEN)
  option(LIBA_JAVASCRIPT "Enable/Disable ffi javascript" 1)
else()
  option(LIBA_JAVASCRIPT "Enable/Disable ffi javascript" 0)
endif()

if(LIBA_JAVASCRIPT)
  if(NOT EMSCRIPTEN)
    find_package(Emscripten)
  endif()

  if(EMSCRIPTEN OR EMSCRIPTEN_FOUND)
    add_subdirectory(javascript)
  endif()
endif()

option(LIBA_SWIG "Enable/Disable ffi swig" 0)

if(LIBA_SWIG)
  if(POLICY CMP0078) # 3.13
    cmake_policy(SET CMP0078 NEW)
  endif() # UseSWIG_TARGET_NAME_PREFERENCE

  if(POLICY CMP0086) # 3.14
    cmake_policy(SET CMP0086 NEW)
  endif() # SWIG_MODULE_NAME

  find_package(SWIG)
endif()

if(LIBA_SWIG AND SWIG_FOUND)
  add_subdirectory(swig)
endif()
