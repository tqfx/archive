add_executable(math test_math.c)
target_link_libraries(math a)
add_test(NAME math COMMAND math)

add_executable(mean test_mean.c)
target_link_libraries(mean a)
add_test(NAME mean COMMAND mean)

add_executable(notefreqs test_notefreqs.c)
target_link_libraries(notefreqs a)
add_test(NAME notefreqs COMMAND notefreqs)

add_executable(hash test_hash.c)
target_link_libraries(hash a)
add_test(NAME hash COMMAND hash)

add_executable(hmac test_hmac.c)
target_link_libraries(hmac a)
add_test(NAME hmac COMMAND hmac)

add_executable(base test_base.c)
target_link_libraries(base a)
add_test(NAME base COMMAND base)

add_executable(crc test_crc.c)
target_link_libraries(crc a)
add_test(NAME crc COMMAND crc)

add_executable(str test_str.c)
target_link_libraries(str a)
add_test(NAME str COMMAND str)

add_executable(vec test_vec.cpp)
target_link_libraries(vec a)
add_test(NAME vec COMMAND vec)

add_executable(list test_list.c)
target_link_libraries(list a)
add_test(NAME list COMMAND list)
