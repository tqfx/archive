option(ENABLE_LUA "Enable ffi lua" OFF)

if(ENABLE_LUA)
  find_package(Lua)
endif()

if(LUA_FOUND)
  if(NOT LUA_MATH_LIBRARY AND ANDROID)
    set(LUA_MATH_LIBRARY m CACHE STRING "lua link math library" FORCE)
  endif()

  add_subdirectory(lua)
endif()

option(ENABLE_JAVA "Enable ffi java" OFF)

if(ENABLE_JAVA)
  find_package(Java)
  find_package(JNI)
endif()

if(Java_FOUND AND JNI_FOUND)
  add_subdirectory(java)
endif()

if(PYTHONINTERP_FOUND)
  add_subdirectory(python)
endif()
