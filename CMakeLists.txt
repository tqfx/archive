include (cmake-arm-none-eabi.cmake)

cmake_minimum_required (VERSION 3.0)

project (CA)

enable_language(ASM)

include (cmake-flags.cmake)

aux_source_directory(. SOURCE_CA)

add_library(ca STATIC ${SOURCE_CA})
