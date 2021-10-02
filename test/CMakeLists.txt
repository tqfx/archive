# test math
add_executable(math test_math.c)
target_link_libraries(math a)

# test notefreqs
add_executable(notefreqs test_notefreqs.c)
target_link_libraries(notefreqs a)
