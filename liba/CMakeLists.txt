cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(LIBA VERSION 1.0.0)

# add source
aux_source_directory(. SOURCE_LIBA)

# add the library
add_library(a STATIC ${SOURCE_LIBA})

# add the binary tree to the search path for include files
target_include_directories(a INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# install the library
install(TARGETS a DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION include FILES_MATCHING PATTERN "*.h")
