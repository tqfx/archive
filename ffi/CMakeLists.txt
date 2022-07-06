option(ENABLE_LUA "Enable ffi lua" OFF)

if(ENABLE_LUA)
  find_package(Lua)
endif()

if(LUA_FOUND)
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

if(Python_Interpreter_FOUND)
  add_subdirectory(python)
endif()
