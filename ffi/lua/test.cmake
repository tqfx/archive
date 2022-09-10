get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

add_test(NAME lua-a WORKING_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
  COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/a.lua
)

add_test(NAME lua-a-pid WORKING_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
  COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/pid.lua
)

add_test(NAME lua-a-polytrack WORKING_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
  COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/polytrack.lua
)

add_test(NAME lua-a-version WORKING_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
  COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/version.lua
)
