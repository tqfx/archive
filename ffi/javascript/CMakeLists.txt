string(FIND "${CMAKE_C_COMPILER}" "emcc" rc)
string(FIND "${CMAKE_CXX_COMPILER}" "em++" rx)
string_remove(CMAKE_C_FLAGS_RELWITHDEBINFO -g)
string_remove(CMAKE_CXX_FLAGS_RELWITHDEBINFO -g)

if(${rc} EQUAL -1)
  set(CMAKE_C_COMPILER ${EMCC})
endif()

if(${rx} EQUAL -1)
  set(CMAKE_CXX_COMPILER ${EMCXX})
endif()

set(CMAKE_EXECUTABLE_SUFFIX ".js")
set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ENABLE_IPO})

# https://emscripten.org/docs/tools_reference/emcc.html
string_append(EMFLAGS -sSINGLE_FILE=1 -sWASM=0)
string_append(EMFLAGS -sWASM_ASYNC_COMPILATION=0)
string_append(EMFLAGS -sEXPORTED_RUNTIME_METHODS=ccall,cwrap)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c src/*.c)

add_executable(a-js ${SOURCES})
set_target_properties(a-js PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINK_FLAGS ${EMFLAGS})
target_include_directories(a-js PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(NOT ENABLE_SANITIZE)
  target_compile_options(a-js PRIVATE $<$<C_COMPILER_ID:Clang>:${CFLAGS}>)
endif()

if(NODE_EXECUTABLE)
  include(test.cmake)
endif()
