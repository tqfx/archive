include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
  pkg_check_modules(TALLOC QUIET talloc)
  set(TALLOC_LIBRARIES "")
  set(TALLOC_FOUND "")
endif()

find_path(TALLOC_INCLUDE_DIR
  NAMES talloc.h
  HINTS ${TALLOC_INCLUDE_DIRS}
)
mark_as_advanced(TALLOC_INCLUDE_DIR)

if(NOT TALLOC_INCLUDE_DIRS)
  list(APPEND TALLOC_INCLUDE_DIRS ${TALLOC_INCLUDE_DIR})
endif()

if(NOT TALLOC_VERSION AND EXISTS ${TALLOC_INCLUDE_DIR}/talloc.h)
  file(STRINGS ${TALLOC_INCLUDE_DIR}/talloc.h talloc_h REGEX "define.*TALLOC_VERSION")
  string(REGEX REPLACE ".*VERSION_MAJOR[^0-9]+([0-9]+).*" "\\1" TALLOC_VERSION_MAJOR ${talloc_h})
  string(REGEX REPLACE ".*VERSION_MINOR[^0-9]+([0-9]+).*" "\\1" TALLOC_VERSION_MINOR ${talloc_h})
  set(TALLOC_VERSION ${TALLOC_VERSION_MAJOR}.${TALLOC_VERSION_MINOR})
  unset(talloc_h)
endif()

find_library(TALLOC_LIBRARY
  NAMES talloc NAMES_PER_DIR
  HINTS ${TALLOC_LIBRARY_DIRS}
)

if(EXISTS ${TALLOC_LIBRARY})
  mark_as_advanced(TALLOC_LIBRARY)
  list(APPEND TALLOC_LIBRARIES ${TALLOC_LIBRARY})
endif()

find_package_handle_standard_args(Talloc
  FOUND_VAR
    TALLOC_FOUND
  REQUIRED_VARS
    TALLOC_LIBRARIES
    TALLOC_INCLUDE_DIRS
  VERSION_VAR
    TALLOC_VERSION
)

if(TALLOC_FOUND)
  if(EXISTS ${TALLOC_LIBRARY})
    add_library(Talloc::talloc UNKNOWN IMPORTED)
    set_target_properties(Talloc::talloc PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${TALLOC_INCLUDE_DIR}
      IMPORTED_LOCATION ${TALLOC_LIBRARY}
      IMPORTED_LINK_INTERFACE_LANGUAGES C
    )
  endif()
endif()
