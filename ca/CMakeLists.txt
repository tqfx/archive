cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(CA VERSION 0)

# check compiler flag
include (../cmake/check_flag.cmake)

# add source
aux_source_directory(. SOURCE_CA)

# add the library
add_library(ca STATIC ${SOURCE_CA})

# add the binary tree to the search path for include files
target_include_directories(ca INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# install the library
install(TARGETS ca DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION include FILES_MATCHING PATTERN "*.h")
