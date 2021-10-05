# test math
ADD_EXECUTABLE(math test_math.c)
TARGET_LINK_LIBRARIES(math a m)

# test notefreqs
ADD_EXECUTABLE(notefreqs test_notefreqs.c)
TARGET_LINK_LIBRARIES(notefreqs a)
