unit_test(math.c math)

unit_test(mean.c mean)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(mean.cpp mean++)
endif()

unit_test(notefreqs.c notefreqs)

unit_test(base.c base)

unit_test(zyx.c zyx)

if(CMAKE_CXX_COMPILER AND CXX IN_LIST enabled_languages)
  unit_test(zyx.cpp zyx++)
endif()

unit_test(str.c str)

unit_test(vec.c vec)

unit_test(list.c list)

unit_test(slist.c slist)

unit_test(mempool.c mempool)
