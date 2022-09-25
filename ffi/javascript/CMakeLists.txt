string(FIND "${CMAKE_C_COMPILER}" "emcc" emcc)
string(FIND "${CMAKE_CXX_COMPILER}" "em++" emxx)
string_remove(CMAKE_C_FLAGS_RELWITHDEBINFO -g)
string_remove(CMAKE_CXX_FLAGS_RELWITHDEBINFO -g)

if(${emcc} EQUAL -1)
  set(CMAKE_C_COMPILER ${EMCC})
endif()

if(${emxx} EQUAL -1)
  set(CMAKE_CXX_COMPILER ${EMCXX})
endif()

set(CMAKE_EXECUTABLE_SUFFIX .js)
set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ENABLE_IPO})
list(FIND CMAKE_C_COMPILER_PREDEFINES_COMMAND -m64 emcc)
list(FIND CMAKE_CXX_COMPILER_PREDEFINES_COMMAND -m64 emxx)

# https://emscripten.org/docs/tools_reference/emcc.html
string_append(EMFLAGS -sSINGLE_FILE=1 -sWASM=0)
string_append(EMFLAGS -sWASM_ASYNC_COMPILATION=0)
string_append(EMFLAGS -sEXPORTED_RUNTIME_METHODS=ccall,cwrap)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c src/*.cc)

add_executable(a-js ${SOURCES})
set_target_properties(a-js PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINK_FLAGS ${EMFLAGS})
target_include_directories(a-js PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(a-js PRIVATE A_REAL_BITS=64)
target_link_libraries(a-js PRIVATE embind)

if(NOT ENABLE_SANITIZE)
  target_compile_options(a-js PRIVATE
    $<$<C_COMPILER_ID:Clang>:${CFLAGS}>
    $<$<CXX_COMPILER_ID:Clang>:${CXXFLAGS}>
  )
endif()

if(${emxx} GREATER 0)
  unset(CMAKE_CXX_COMPILER_ARG${emxx} CACHE)
  unset(CMAKE_CXX_COMPILER_ARG${emxx})
endif()

if(${emcc} GREATER 0)
  unset(CMAKE_C_COMPILER_ARG${emcc} CACHE)
  unset(CMAKE_C_COMPILER_ARG${emcc})
endif()

if(NODE_EXECUTABLE)
  include(test.cmake)
endif()
