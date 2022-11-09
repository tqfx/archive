if(CMAKE_C_COMPILER_ID MATCHES "MSVC" OR CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  string_append(CMAKE_CXX_FLAGS /W4 /sdl)
  string_append(CMAKE_C_FLAGS /W4 /sdl)
else()
  string_append(CMAKE_CXX_FLAGS -pedantic -Wall -Weffc++)
  string_append(CMAKE_C_FLAGS -pedantic -Wall)
endif()

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
string_append(CMAKE_CXX_FLAGS ${CXXFLAGS_WARNINGS} ${CXXFLAGS_SANITIZE})
string_append(CMAKE_C_FLAGS ${CFLAGS_WARNINGS} ${CFLAGS_SANITIZE})
string_append(CMAKE_EXE_LINKER_FLAGS ${LDFLAGS_SANITIZE})
set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})

if(DEFINED ENV{ANDROID_ROOT})
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# https://cmake.org/cmake/help/latest/module/CheckPIESupported.html
if(CMAKE_VERSION VERSION_GREATER 3.14)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
endif()

if(ENABLE_SANITIZE)
  set(A_LIBRARY a-san)
else()
  set(A_LIBRARY a)
endif()

set(TARGET_PREFIX test-)

function(building target)
  set(TARGET "${TARGET_PREFIX}${target}")

  if(NOT CXX IN_LIST ENABLED_LANGUAGES)
    list(FILTER ARGN INCLUDE REGEX ".c$")
  endif()

  add_executable(${TARGET} ${ARGN})
  set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${target})
  target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME}::${A_LIBRARY})
  target_executable_options(${TARGET})
endfunction()

function(unittest target)
  set(TARGET "${TARGET_PREFIX}${target}")
  cmake_parse_arguments(TEST "" "NAME" "ARGS" ${ARGN})

  if(NOT TEST_NAME)
    set(TEST_NAME ${target})
  endif()

  add_test(NAME ${TEST_NAME} WORKING_DIRECTORY
    $<IF:${IS_MULTI_CONFIG},$<TARGET_FILE_DIR:${A_LIBRARY}>,${CMAKE_CURRENT_BINARY_DIR}>
    COMMAND ${TARGET_SYSTEM_EMULATOR} $<TARGET_FILE:${TARGET}> ${TEST_ARGS}
  )
endfunction()

building(a lib.c lib.cpp)
unittest(a NAME bkdr ARGS bkdr bkdr)
unittest(a NAME for ARGS for 10)
unittest(a)

building(main main.c main.cpp)
unittest(main)

building(math math.c math.cpp)
unittest(math)

building(version version.c version.cpp)
unittest(version)

building(arr arr.c arr.cpp)
unittest(arr)

building(crc crc.c crc.cpp)
unittest(crc ARGS crc.c)

building(list list.c list.cpp)
unittest(list)

building(slist slist.c slist.cpp)
unittest(slist)

building(complex complex.c complex.cpp)
unittest(complex ARGS -4,3 -2,1)

building(pid pid.c pid.cpp)
unittest(pid)

building(fpid fpid.c fpid.cpp)
unittest(fpid)

building(poly poly.c poly.cpp)
unittest(poly)

building(polytrack polytrack.c polytrack.cpp)
unittest(polytrack)

building(notefreqs notefreqs.c notefreqs.cpp)
unittest(notefreqs)

building(operator operator.c operator.cpp)
unittest(operator)

add_subdirectory(host)
