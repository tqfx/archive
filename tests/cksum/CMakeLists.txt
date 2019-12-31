add_executable(test-crc crc.c)
set_target_properties(test-crc PROPERTIES OUTPUT_NAME crc)
target_link_libraries(test-crc ${PROJECT_NAME})
add_test(NAME test-crc COMMAND crc crc_tab.c)

add_executable(test-hash hash.c)
set_target_properties(test-hash PROPERTIES OUTPUT_NAME hash)
target_link_libraries(test-hash ${PROJECT_NAME})
add_test(NAME test-hash COMMAND hash)

add_executable(test-hmac hmac.c)
set_target_properties(test-hmac PROPERTIES OUTPUT_NAME hmac)
target_link_libraries(test-hmac ${PROJECT_NAME})
add_test(NAME test-hmac COMMAND hmac)
