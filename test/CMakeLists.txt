add_executable(testa a.c)
target_link_libraries(testa ${PROJECT_NAME})
set_target_properties(testa PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
add_test(NAME testa COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

add_executable(math math.c)
target_link_libraries(math ${PROJECT_NAME})
add_test(NAME math COMMAND math)

add_executable(mean mean.c)
target_link_libraries(mean ${PROJECT_NAME})
add_test(NAME mean COMMAND mean)

add_executable(notefreqs notefreqs.c)
target_link_libraries(notefreqs ${PROJECT_NAME})
add_test(NAME notefreqs COMMAND notefreqs)

add_executable(hash hash.c)
target_link_libraries(hash ${PROJECT_NAME})
add_test(NAME hash COMMAND hash)

add_executable(hmac hmac.c)
target_link_libraries(hmac ${PROJECT_NAME})
add_test(NAME hmac COMMAND hmac)

add_executable(base base.c)
target_link_libraries(base ${PROJECT_NAME})
add_test(NAME base COMMAND base)

add_executable(crc crc.c)
target_link_libraries(crc ${PROJECT_NAME})
add_test(NAME crc COMMAND crc crc_tab.c)

add_executable(str str.c)
target_link_libraries(str ${PROJECT_NAME})
add_test(NAME str COMMAND str)

add_executable(vec vec.c)
target_link_libraries(vec ${PROJECT_NAME})
add_test(NAME vec COMMAND vec)

add_executable(list list.c)
target_link_libraries(list ${PROJECT_NAME})
add_test(NAME list COMMAND list)

add_executable(mempool mempool.c)
target_link_libraries(mempool ${PROJECT_NAME})
add_test(NAME mempool COMMAND mempool)
