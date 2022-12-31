include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
  if(CMAKE_VERSION VERSION_GREATER 3.6)
    pkg_check_modules(ReadLine QUIET IMPORTED_TARGET readline tinfo)
  else()
    pkg_check_modules(ReadLine QUIET readline tinfo)
  endif()

  if(ReadLine_FOUND)
    if(ReadLine_VERSION)
      set(READLINE_VERSION ${ReadLine_VERSION})
    endif()

    if(ReadLine_CFLAGS)
      set(READLINE_CFLAGS ${ReadLine_CFLAGS})
    endif()
  endif()
endif()

find_path(READLINE_INCLUDE_DIR
  NAMES readline/readline.h
  HINTS ${ReadLine_INCLUDE_DIRS}
)
mark_as_advanced(READLINE_INCLUDE_DIR)

if(NOT READLINE_VERSION AND EXISTS ${READLINE_INCLUDE_DIR}/readline/readline.h)
  file(STRINGS ${READLINE_INCLUDE_DIR}/readline/readline.h readline_h REGEX ".*READLINE_VERSION.*")
  string(REGEX REPLACE ".*0x([0-9]+).*" "\\1" READLINE_VERSION ${readline_h})
  math(EXPR READLINE_VERSION_MAJOR "${READLINE_VERSION}/100")
  math(EXPR READLINE_VERSION_MINOR "${READLINE_VERSION}%100")
  set(READLINE_VERSION
    ${READLINE_VERSION_MAJOR}.${READLINE_VERSION_MINOR}
  )
  unset(readline_h)
endif()

find_library(READLINE_LIBRARY
  NAMES readline NAMES_PER_DIR
  HINTS ${ReadLine_LIBRARY_DIRS}
)

if(EXISTS ${READLINE_LIBRARY})
  mark_as_advanced(READLINE_LIBRARY)
  list(APPEND READLINE_LIBRARIES ${READLINE_LIBRARY})
endif()

find_library(TINFO_LIBRARY
  NAMES tinfo NAMES_PER_DIR
  HINTS ${ReadLine_LIBRARY_DIRS}
)

if(EXISTS ${TINFO_LIBRARY})
  mark_as_advanced(TINFO_LIBRARY)
  list(APPEND READLINE_LIBRARIES ${TINFO_LIBRARY})
endif()

find_package_handle_standard_args(ReadLine
  FOUND_VAR
    READLINE_FOUND
  REQUIRED_VARS
    READLINE_LIBRARIES
    READLINE_INCLUDE_DIR
  VERSION_VAR
    READLINE_VERSION
)

if(READLINE_FOUND)
  if(TARGET PkgConfig::ReadLine)
    add_library(ReadLine::readline ALIAS PkgConfig::ReadLine)
  endif()

  if(NOT TARGET ReadLine::tinfo AND EXISTS ${TINFO_LIBRARY})
    add_library(ReadLine::tinfo UNKNOWN IMPORTED)
    set_target_properties(ReadLine::tinfo PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${READLINE_INCLUDE_DIR}
      INTERFACE_COMPILE_OPTIONS "${READLINE_CFLAGS}"
      IMPORTED_LOCATION ${TINFO_LIBRARY}
      IMPORTED_LINK_INTERFACE_LANGUAGES C
    )
  endif()

  if(NOT TARGET ReadLine::readline AND EXISTS ${READLINE_LIBRARY})
    add_library(ReadLine::readline UNKNOWN IMPORTED)
    set_target_properties(ReadLine::readline PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${READLINE_INCLUDE_DIR}
      INTERFACE_COMPILE_OPTIONS "${READLINE_CFLAGS}"
      IMPORTED_LOCATION ${READLINE_LIBRARY}
      IMPORTED_LINK_INTERFACE_LANGUAGES C
    )

    if(NOT TARGET PkgConfig::ReadLine AND TARGET ReadLine::tinfo)
      set_target_properties(ReadLine::readline PROPERTIES
        INTERFACE_LINK_LIBRARIES ReadLine::tinfo
      )
    endif()
  endif()
endif()
