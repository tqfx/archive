unit_test(mf.c mf)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(mf.cpp mf++)
endif()

unit_test(pid.c pid)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(pid.cpp pid++)
endif()

unit_test(fpid.c fpid)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(fpid.cpp fpid++)
endif()

unit_test(fuzzy.c fuzzy)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(fuzzy.cpp fuzzy++)
endif()
