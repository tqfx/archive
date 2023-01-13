#.rst:
# FindCython
# ----------
#
# Find cython executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``CYTHON_FOUND``
#
# ``CYTHON_EXECUTABLE``
#
# ``CYTHON_VERSION``
#
# ``CYTHON_VERSION_MAJOR``
#
# ``CYTHON_VERSION_MINOR``
#
# ``CYTHON_VERSION_PATCH``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

if(EXISTS "${Python_EXECUTABLE}")
  execute_process(COMMAND ${Python_EXECUTABLE} -c "import Cython; print(Cython.__version__)"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE CYTHON_VERSION
  )
endif()

if(CYTHON_VERSION)
  set(CYTHON_EXECUTABLE ${Python_EXECUTABLE} -m cython)
else()
  find_program(CYTHON_EXECUTABLE NAMES cython)
  mark_as_advanced(CYTHON_EXECUTABLE)
  set(CYTHON_VERSION)
endif()

if(NOT CYTHON_VERSION AND EXISTS "${CYTHON_EXECUTABLE}")
  execute_process(COMMAND ${CYTHON_EXECUTABLE} --version OUTPUT_QUIET ERROR_VARIABLE CYTHON_VERSION)
  string(REGEX REPLACE ".*version[^0-9]+([^\n ]+).*" "\\1" CYTHON_VERSION "${CYTHON_VERSION}")
endif()

string(REGEX REPLACE "^[^.]+\\.[^.]+\\.([^.]+).*" "\\1" CYTHON_VERSION_PATCH "${CYTHON_VERSION}")
string(REGEX REPLACE "^[^.]+\\.([^.]+).*" "\\1" CYTHON_VERSION_MINOR "${CYTHON_VERSION}")
string(REGEX REPLACE "^([^.]+).*" "\\1" CYTHON_VERSION_MAJOR "${CYTHON_VERSION}")

find_package_handle_standard_args(Cython
  FOUND_VAR
    CYTHON_FOUND
  REQUIRED_VARS
    CYTHON_EXECUTABLE
  VERSION_VAR
    CYTHON_VERSION
)
