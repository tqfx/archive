add_executable(test-crc crc.c)
set_target_properties(test-crc PROPERTIES OUTPUT_NAME crc)
target_link_libraries(test-crc ${DEFAULT_NAME})
add_test(NAME test-crc COMMAND $<TARGET_FILE:test-crc> crc_tab.c)

add_executable(test-hash hash.c)
set_target_properties(test-hash PROPERTIES OUTPUT_NAME hash)
target_link_libraries(test-hash ${DEFAULT_NAME})
add_test(NAME test-hash COMMAND $<TARGET_FILE:test-hash>)

add_executable(test-hmac hmac.c)
set_target_properties(test-hmac PROPERTIES OUTPUT_NAME hmac)
target_link_libraries(test-hmac ${DEFAULT_NAME})
add_test(NAME test-hmac COMMAND $<TARGET_FILE:test-hmac>)
