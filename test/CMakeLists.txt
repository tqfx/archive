if(
  "${CMAKE_C_COMPILER_ID}" MATCHES "MSVC" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC"
)
  foreach(v /W4 /sdl)
    string_append(CMAKE_C_FLAGS ${v})
    string_append(CMAKE_CXX_FLAGS ${v})
  endforeach()
else()
  foreach(v -Wall -Wextra -Wpedantic)
    string_append(CMAKE_C_FLAGS ${v})
    string_append(CMAKE_CXX_FLAGS ${v})
  endforeach()

  string_append(CMAKE_CXX_FLAGS -Weffc++)
endif()

foreach(v ${CFLAGS})
  string_append(CMAKE_C_FLAGS ${v})
endforeach()

foreach(v ${CXXFLAGS})
  string_append(CMAKE_CXX_FLAGS ${v})
endforeach()

if(ANDROID)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})
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

unittest(pid SOURCE pid.c pid.cpp)
unittest(fpid SOURCE fpid.c fpid.cpp)
unittest(notefreqs SOURCE notefreqs.c)
unittest(poly SOURCE poly.c poly.cpp)
unittest(polytrack SOURCE polytrack.c polytrack.cpp)

unittest(operator SOURCE operator.c)

add_subdirectory(host)
