find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
find_program(CLANG_FORMAT clang-format)
find_program(CLANG_TIDY clang-tidy)
find_program(CPPCHECK cppcheck)
find_program(CPPLINT cpplint)
mark_as_advanced(
  INCLUDE_WHAT_YOU_USE
  CLANG_FORMAT
  CLANG_TIDY
  CPPCHECK
  CPPLINT
)

function(target_library_option_ target scope)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "^C|CXX")
  set_target_properties(${target} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${ENABLE_IPO})

  foreach(lang ${ENABLED_LANGUAGES})
    set_target_properties(${target} PROPERTIES ${lang}_VISIBILITY_PRESET hidden)

    if(ENABLE_IYWU AND INCLUDE_WHAT_YOU_USE)
      set_target_properties(${target} PROPERTIES ${lang}_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
    endif()

    if(ENABLE_CLANG_TIDY AND CLANG_TIDY)
      set_target_properties(${target} PROPERTIES ${lang}_CLANG_TIDY "${CLANG_TIDY};--fix")
    endif()

    if(ENABLE_CPPCHECK AND CPPCHECK)
      set_target_properties(${target} PROPERTIES ${lang}_CPPCHECK "${CPPCHECK};--enable=warning,performance")
    endif()

    target_compile_options(${target} ${scope} $<IF:$<${lang}_COMPILER_ID:MSVC>,/W4 /sdl,-pedantic -Wall>)
  endforeach()

  target_compile_options(${target} ${scope} $<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<COMPILE_LANGUAGE:CXX>>:-Weffc++>)

  foreach(lang ${ENABLED_LANGUAGES})
    target_compile_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_WARNINGS}>)
  endforeach()

  if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib AND CMAKE_C_COMPILER_ID MATCHES "TinyCC")
    set_target_properties(${target} PROPERTIES IMPORT_SUFFIX .def)
  endif()
endfunction()

function(target_library_options)
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    target_library_option_(${target} ${scope})
  endforeach()
endfunction()

function(target_executable_option_ target scope)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "^C|CXX")
  set_target_properties(${target} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${ENABLE_IPO})

  foreach(lang ${ENABLED_LANGUAGES})
    if(ENABLE_IYWU AND INCLUDE_WHAT_YOU_USE)
      set_target_properties(${target} PROPERTIES ${lang}_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
    endif()

    if(ENABLE_CLANG_TIDY AND CLANG_TIDY)
      set_target_properties(${target} PROPERTIES ${lang}_CLANG_TIDY "${CLANG_TIDY};--fix")
    endif()

    if(ENABLE_CPPCHECK AND CPPCHECK)
      set_target_properties(${target} PROPERTIES ${lang}_CPPCHECK "${CPPCHECK};--enable=warning,performance")
    endif()
  endforeach()

  if(CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND MINGW)
    # https://fedoraproject.org/wiki/MinGW/Configure_wine
    target_link_options(${target} ${scope} -static-libgcc
      $<$<COMPILE_LANGUAGE:CXX>:-static-libstdc++>
      -Wl,-Bstatic,--whole-archive
      -lwinpthread
      -Wl,--no-whole-archive
    )
  endif()
endfunction()

function(target_executable_options)
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    target_executable_option_(${target} ${scope})

    if(CXX IN_LIST ENABLED_LANGUAGES)
      target_compile_definitions(${target} ${scope} HAS_CXX)
    endif()
  endforeach()
endfunction()

function(target_compile_sanitize)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "^C|CXX")
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      target_compile_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_SANITIZE}>)
    endforeach()
  endforeach()
endfunction()

function(target_link_sanitize)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "^C|CXX")
  set(scope PRIVATE)

  if(MSVC)
    return()
  endif()

  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      target_link_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_SANITIZE}>)
    endforeach()

    target_link_options(${target} ${scope} ${LDFLAGS_SANITIZE})
  endforeach()
endfunction()

function(target_compile_warnings)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "^C|CXX")
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      target_compile_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_WARNINGS}>)
    endforeach()
  endforeach()
endfunction()
