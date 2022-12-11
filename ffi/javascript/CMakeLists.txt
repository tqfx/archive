string(FIND "${CMAKE_CXX_COMPILER}" "em++" emxx)
string(FIND "${CMAKE_C_COMPILER}" "emcc" emcc)

if(${emxx} EQUAL -1)
  set(CMAKE_CXX_COMPILER ${EMCXX})
endif()

if(${emcc} EQUAL -1)
  set(CMAKE_C_COMPILER ${EMCC})
endif()

set(CMAKE_EXECUTABLE_SUFFIX .js)
set(CMAKE_POSITION_INDEPENDENT_CODE ${LIBA_PIC})
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${LIBA_IPO})
list(FIND CMAKE_C_COMPILER_PREDEFINES_COMMAND -m64 emcc)
list(FIND CMAKE_CXX_COMPILER_PREDEFINES_COMMAND -m64 emxx)

# https://emscripten.org/docs/tools_reference/emcc.html
string_append(LDFLAGS -sSINGLE_FILE=1 -sWASM=0)
string_append(LDFLAGS -sWASM_ASYNC_COMPILATION=0)
string_append(LDFLAGS -sEXPORTED_RUNTIME_METHODS=ccall,cwrap)

if(EMSCRIPTEN)
  set(OBJECTS $<TARGET_OBJECTS:a>)
else()
  set(OBJECTS $<TARGET_PROPERTY:a,SOURCES>)
endif()

file(GLOB_RECURSE SOURCES src/*.[ch]*)
add_executable(a-js ${OBJECTS} ${SOURCES})
target_compile_definitions(a-js PRIVATE $<TARGET_PROPERTY:a,COMPILE_DEFINITIONS>)
target_include_directories(a-js PRIVATE $<TARGET_PROPERTY:a,INCLUDE_DIRECTORIES>)
set_target_properties(a-js PROPERTIES LINK_FLAGS ${LDFLAGS} OUTPUT_NAME liba)
target_link_libraries(a-js PRIVATE embind)

if(LIBA_WARNINGS)
  target_compile_options(a-js PRIVATE -Weverything -Wno-documentation
    -Wno-documentation-unknown-command -Wno-used-but-marked-unused
    $<$<COMPILE_LANGUAGE:C>:-Wno-declaration-after-statement>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-c++98-compat-pedantic>
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
