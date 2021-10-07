# test math
ADD_EXECUTABLE(math test_math.c)
TARGET_LINK_LIBRARIES(math a m)

# test notefreqs
ADD_EXECUTABLE(notefreqs test_notefreqs.c)
TARGET_LINK_LIBRARIES(notefreqs a)

# test md5
ADD_EXECUTABLE(md5 test_md5.c)
TARGET_LINK_LIBRARIES(md5 a)

# test sha1
ADD_EXECUTABLE(sha1 test_sha1.c)
TARGET_LINK_LIBRARIES(sha1 a)

# test sha256
ADD_EXECUTABLE(sha256 test_sha256.c)
TARGET_LINK_LIBRARIES(sha256 a)

# test sha224
ADD_EXECUTABLE(sha224 test_sha224.c)
TARGET_LINK_LIBRARIES(sha224 a)
