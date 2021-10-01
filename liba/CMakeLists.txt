cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(a VERSION 1.0.0)

# set the target name
set(TARGET_NAME ${PROJECT_NAME})

# specify the C standard
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# specify the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

# add source
aux_source_directory(. SOURCE)

# add the library
add_library(${TARGET_NAME} STATIC ${SOURCE})

# add the binary tree to the search path for include files
target_include_directories(${TARGET_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# install the library
foreach(_suffix "*.h" "*.hpp")
  file(GLOB_RECURSE _include ${_suffix})
  install(FILES ${_include} DESTINATION include)
endforeach(_suffix "*.h" "*.hpp")
install(TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(EXPORT ${TARGET_NAME}-targets
  FILE ${TARGET_NAME}-config.cmake
  DESTINATION lib/cmake/${TARGET_NAME}
)
