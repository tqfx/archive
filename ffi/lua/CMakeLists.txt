file(GLOB_RECURSE SOURCES src/*.c)

add_library(lua-a SHARED ${SOURCES})
set_target_properties(lua-a PROPERTIES OUTPUT_NAME a)
target_link_libraries(lua-a PRIVATE ${LUA_LIBRARIES} a)
target_compile_options(lua-a PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang,IntelLLVM>:-Wall -Wextra -Wpedantic>
  $<$<C_COMPILER_ID:MSVC>:/W4 /sdl> $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
)
target_include_directories(lua-a PRIVATE ${LUA_INCLUDE_DIR})

if(LUA_VERSION_MAJOR AND LUA_VERSION_MINOR)
  set(LUA_VERSION ${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR})
endif()

install(TARGETS lua-a
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION lib/lua/${LUA_VERSION}
  LIBRARY DESTINATION lib/lua/${LUA_VERSION}
  RUNTIME DESTINATION lib/lua/${LUA_VERSION}
)

find_program(LUA_EXECUTABLE NAMES lua
  lua${LUA_VERSION_MAJOR}${LUA_VERSION_MINOR}
  lua${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  lua-${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  lua.${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  HINTS ENV LUA_DIR
)

add_test(NAME test-lua-a
  COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/a.lua
)
