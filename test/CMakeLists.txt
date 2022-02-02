add_executable(atest a.c)
target_link_libraries(atest a)
set_target_properties(atest PROPERTIES OUTPUT_NAME a)
add_test(NAME atest COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/a)

add_executable(math math.cpp)
target_link_libraries(math a)
add_test(NAME math COMMAND math)

add_executable(mean mean.cpp)
target_link_libraries(mean a)
add_test(NAME mean COMMAND mean)

add_executable(notefreqs notefreqs.cpp)
target_link_libraries(notefreqs a)
add_test(NAME notefreqs COMMAND notefreqs)

add_executable(hash hash.cpp)
target_link_libraries(hash a)
add_test(NAME hash COMMAND hash)

add_executable(hmac hmac.cpp)
target_link_libraries(hmac a)
add_test(NAME hmac COMMAND hmac)

add_executable(base base.cpp)
target_link_libraries(base a)
add_test(NAME base COMMAND base)

add_executable(crc crc.cpp)
target_link_libraries(crc a)
add_test(NAME crc COMMAND crc)

add_executable(str str.cpp)
target_link_libraries(str a)
add_test(NAME str COMMAND str)

add_executable(vec vec.cpp)
target_link_libraries(vec a)
add_test(NAME vec COMMAND vec)

add_executable(list list.cpp)
target_link_libraries(list a)
add_test(NAME list COMMAND list)
