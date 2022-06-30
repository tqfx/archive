get_property(enabled_languages GLOBAL PROPERTY ENABLED_LANGUAGES)

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
endif()

foreach(v ${C_FLAGS})
  string_append(CMAKE_C_FLAGS ${v})
endforeach()

foreach(v ${CXX_FLAGS})
  string_append(CMAKE_CXX_FLAGS ${v})
endforeach()

if(ENABLED_IPO)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

foreach(lang ${enabled_languages})
  if(ENABLE_IYWU AND INCLUDE_WHAT_YOU_USE)
    set(CMAKE_${lang}_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
  endif()

  if(ENABLE_CLANG_TIDY AND CLANG_TIDY)
    set(CMAKE_${lang}_CLANG_TIDY ${CLANG_TIDY} --fix)
  endif()

  if(ENABLE_CPPCHECK AND CPPCHECK)
    set(CMAKE_${lang}_CPPCHECK ${CPPCHECK} --enable=warning,performance)
  endif()

  if(CMAKE_${lang}_LINK_OPTIONS_NO_PIE AND NOT ANDROID)
    string_append(CMAKE_${lang}_LINK_FLAGS ${CMAKE_${lang}_LINK_OPTIONS_NO_PIE})
  endif()
endforeach()

function(unit_test source target)
  set(TARGET ${LIBRARY_NAME}-test-${target})
  add_executable(${TARGET} ${source})
  set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${target})
  target_link_libraries(${TARGET} ${PROJECT_NAME}::${LIBRARY_NAME})
  add_test(NAME ${TARGET} COMMAND ${TARGET_SYSTEM_EMULATOR} $<TARGET_FILE:${TARGET}> ${ARGN})
endfunction()

unit_test(test.c ${LIBRARY_NAME})

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(test.cpp ${LIBRARY_NAME}++)
endif()

unit_test(real.c real)

unit_test(imag.c imag)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(imag.cpp imag++)
endif()

add_subdirectory(misc)
add_subdirectory(poly)
add_subdirectory(cksum)
add_subdirectory(filter)
add_subdirectory(controller)
