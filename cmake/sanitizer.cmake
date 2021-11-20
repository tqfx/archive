# include modules
include(${CMAKE_CURRENT_LIST_DIR}/append_option.cmake)
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  append_flag(-fno-omit-frame-pointer -fsanitize=address)
  append_flag(-fsanitize=undefined)
  append_flag(-fsanitize=leak)
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  append_flag(/fsanitize=address)
endif()
