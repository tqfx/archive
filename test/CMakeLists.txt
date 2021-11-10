add_executable(test test.c)
target_link_libraries(test a)

add_executable(math test_math.c)
target_link_libraries(math a)

add_executable(mean test_mean.c)
target_link_libraries(mean a)

add_executable(notefreqs test_notefreqs.c)
target_link_libraries(notefreqs a)

add_executable(hash test_hash.c)
target_link_libraries(hash a)

add_executable(hmac test_hmac.c)
target_link_libraries(hmac a)

add_executable(base test_base.c)
target_link_libraries(base a)

add_executable(str test_str.c)
target_link_libraries(str a)

add_executable(vec test_vec.cpp)
target_link_libraries(vec a)

add_executable(list test_list.c)
target_link_libraries(list a)

add_executable(crctab test_crctab.c)
target_link_libraries(crctab a)
