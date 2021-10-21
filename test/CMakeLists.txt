add_executable(test test.c)
target_link_libraries(test a)

add_executable(test_math test_math.c)
target_link_libraries(test_math a)

add_executable(test_notefreqs test_notefreqs.c)
target_link_libraries(test_notefreqs a)

add_executable(test_hash test_hash.c)
target_link_libraries(test_hash a)

add_executable(test_hmac test_hmac.c)
target_link_libraries(test_hmac a)

add_executable(test_base test_base.c)
target_link_libraries(test_base a)
