unit_test(lpf.c lpf)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(lpf.cpp lpf++)
endif()
