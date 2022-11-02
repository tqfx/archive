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

if(NOT ANDROID)
  set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})
else()
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

function(unittest target)
  cmake_parse_arguments(TEST "" "TARGET" "SOURCE;COMMAND" ${ARGN})

  if(NOT CXX IN_LIST ENABLED_LANGUAGES)
    list(FILTER TEST_SOURCE INCLUDE REGEX ".c$")
  endif()

  if(TEST_SOURCE)
    if(TEST_TARGET)
      set(TARGET ${TEST_TARGET})
    else()
      set(TARGET test-${target})
    endif()

    add_executable(${TARGET} ${TEST_SOURCE})
    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${target})
    target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME}::${A_LIBRARY})
    add_test(NAME ${target} WORKING_DIRECTORY
      $<IF:${IS_MULTI_CONFIG},$<TARGET_FILE_DIR:a>,${CMAKE_CURRENT_BINARY_DIR}>
      COMMAND ${TARGET_SYSTEM_EMULATOR} $<TARGET_FILE:${TARGET}> ${TEST_COMMAND}
    )
    target_executable_options(${TARGET})
  endif()
endfunction()

unittest(a SOURCE lib.cpp)

unittest(for SOURCE for.c for.cpp)

unittest(version SOURCE version.cpp)

unittest(bkdr SOURCE bkdr.c)
unittest(real SOURCE real.c)
unittest(math SOURCE math.c)

unittest(arr SOURCE arr.c arr.cpp)
unittest(list SOURCE list.c list.cpp)
unittest(slist SOURCE slist.c slist.cpp)
unittest(crc SOURCE crc.cpp COMMAND crc.c)
unittest(complex SOURCE complex.c complex.cpp COMMAND -4,3 -2,1)

unittest(pid SOURCE pid.c pid.cpp)
unittest(fpid SOURCE fpid.c fpid.cpp)
unittest(notefreqs SOURCE notefreqs.c)
unittest(poly SOURCE poly.c poly.cpp)
unittest(polytrack SOURCE polytrack.c polytrack.cpp)

unittest(operator SOURCE operator.c)

add_subdirectory(host)
