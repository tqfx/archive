find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
find_program(CLANG_FORMAT clang-format)
find_program(CLANG_TIDY clang-tidy)
find_program(CPPCHECK cppcheck)
find_program(CPPLINT cpplint)

function(target_library_option_ target scope)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "C|CXX")
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

    target_compile_options(${target} ${scope} $<IF:$<${lang}_COMPILER_ID:MSVC>,/W4 /sdl,-Wall -Wextra -Wpedantic>)
  endforeach()

  target_compile_options(${target} ${scope}
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-Weffc++>
  )

  foreach(lang ${ENABLED_LANGUAGES})
    list(APPEND ${lang}FLAGS ${${lang}FLAGS_WARNINGS} ${${lang}FLAGS_SANITIZE})
    target_compile_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS}>)
  endforeach()
endfunction()

function(target_library_options)
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if("${target}" MATCHES "INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    target_library_option_(${target} ${scope})
  endforeach()
endfunction()

function(target_executable_option_ target scope)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "C|CXX")
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

  if(MINGW)
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
    if("${target}" MATCHES "INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    target_executable_option_(${target} ${scope})
  endforeach()
endfunction()

function(target_compile_sanitize)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "C|CXX")
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if("${target}" MATCHES "INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      target_compile_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_SANITIZE}>)
    endforeach()
  endforeach()
endfunction()

function(target_link_sanitize)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "C|CXX")
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if("${target}" MATCHES "INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      target_link_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_SANITIZE}>)
    endforeach()
  endforeach()
endfunction()

function(target_compile_warnings)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "C|CXX")
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if("${target}" MATCHES "INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      target_compile_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_WARNINGS}>)
    endforeach()
  endforeach()
endfunction()

function(target_link_warnings)
  list(FILTER ENABLED_LANGUAGES INCLUDE REGEX "C|CXX")
  set(scope PRIVATE)

  foreach(target ${ARGN})
    if("${target}" MATCHES "INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()

    foreach(lang ${ENABLED_LANGUAGES})
      continue()
      target_link_options(${target} ${scope} $<$<COMPILE_LANGUAGE:${lang}>:${${lang}FLAGS_WARNINGS}>)
    endforeach()
  endforeach()
endfunction()
