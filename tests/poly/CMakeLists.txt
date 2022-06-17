unit_test(polytrack.c polytrack)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(polytrack.cpp polytrack+)
endif()
