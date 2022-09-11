set(CMAKE_C_COMPILER ${EMCC})
set(CMAKE_CXX_COMPILER ${EMCXX})
set(CMAKE_EXECUTABLE_SUFFIX ".js")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ENABLE_IPO})

# https://emscripten.org/docs/tools_reference/emcc.html
string_append(EMFLAGS -sSINGLE_FILE=1 -sWASM=0)
string_append(EMFLAGS -sWASM_ASYNC_COMPILATION=0)
string_append(EMFLAGS -sEXPORTED_RUNTIME_METHODS=ccall,cwrap)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c src/*.c)

add_executable(a-js ${SOURCES})
set_target_properties(a-js PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINK_FLAGS ${EMFLAGS})
target_include_directories(a-js PRIVATE ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE TESTS ${CMAKE_CURRENT_LIST_DIR}/test/*.js)
add_custom_command(TARGET a-js POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TESTS} ${CMAKE_CURRENT_BINARY_DIR}
)

find_program(NODE_EXECUTABLE node)

if(NODE_EXECUTABLE)
  include(test.cmake)
endif()
