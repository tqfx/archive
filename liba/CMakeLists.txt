CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# set the project name and version
PROJECT(a VERSION 1.0.0)

# set the target name
SET(TARGET_NAME ${PROJECT_NAME})

# specify the C standard
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(CMAKE_C_STANDARD 11)

# specify the C++ standard
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 11)

# add source
AUX_SOURCE_DIRECTORY(. SOURCE)

# add the library
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCE})

# add the binary tree to the search path for include files
TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# install the library
FOREACH(_suffix "*.h" "*.hpp")
  FILE(GLOB_RECURSE _include ${_suffix})
  INSTALL(FILES ${_include} DESTINATION include)
ENDFOREACH(_suffix "*.h" "*.hpp")
INSTALL(TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
INSTALL(EXPORT ${TARGET_NAME}-targets
  FILE ${TARGET_NAME}-config.cmake
  DESTINATION lib/cmake/${TARGET_NAME}
)
