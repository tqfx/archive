if(
  "${CMAKE_C_COMPILER_ID}" MATCHES "MSVC" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC"
)
  string_append(CMAKE_C_FLAGS /W4 /sdl)
  string_append(CMAKE_CXX_FLAGS /W4 /sdl)
else()
  string_append(CMAKE_C_FLAGS -Wall -Wextra -Wpedantic)
  string_append(CMAKE_CXX_FLAGS -Wall -Wextra -Wpedantic -Weffc++)
endif()

string_append(CMAKE_C_FLAGS ${CFLAGS_WARNINGS} ${CFLAGS_SANITIZE})
string_append(CMAKE_CXX_FLAGS ${CXXFLAGS_WARNINGS} ${CXXFLAGS_SANITIZE})

if(NOT ANDROID)
  set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.13)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
endif()

function(unittest target)
  cmake_parse_arguments(TEST "" "TARGET" "SOURCE;COMMAND" ${ARGN})

  if(NOT TEST_TARGET)
    set(TARGET test-${target})
  else()
    set(TARGET ${TEST_TARGET})
  endif()

  add_executable(${TARGET} ${TEST_SOURCE})
  target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME}::a)
  set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${target})
  add_test(NAME ${target} COMMAND ${TARGET_SYSTEM_EMULATOR} $<TARGET_FILE:${TARGET}> ${TEST_COMMAND})
  target_executable_options(${TARGET})
endfunction()

unittest(a SOURCE lib.cpp)

unittest(for SOURCE for.c for.cpp)

unittest(version SOURCE version.cpp)

unittest(real SOURCE real.c)
unittest(math SOURCE math.c)

unittest(arr SOURCE arr.c arr.cpp)
unittest(list SOURCE list.c list.cpp)
unittest(slist SOURCE slist.c slist.cpp)
unittest(crc SOURCE crc.cpp COMMAND crc.c)

unittest(pid SOURCE pid.c pid.cpp)
unittest(fpid SOURCE fpid.c fpid.cpp)
unittest(notefreqs SOURCE notefreqs.c)
unittest(poly SOURCE poly.c poly.cpp)
unittest(polytrack SOURCE polytrack.c polytrack.cpp)

unittest(operator SOURCE operator.c)

add_subdirectory(host)
