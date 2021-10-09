# test math
ADD_EXECUTABLE(math test_math.c)
TARGET_LINK_LIBRARIES(math a m)

# test notefreqs
ADD_EXECUTABLE(notefreqs test_notefreqs.c)
TARGET_LINK_LIBRARIES(notefreqs a)

# test md2
ADD_EXECUTABLE(md2 test_md2.c)
TARGET_LINK_LIBRARIES(md2 a)

# test md4
ADD_EXECUTABLE(md4 test_md4.c)
TARGET_LINK_LIBRARIES(md4 a)

# test md5
ADD_EXECUTABLE(md5 test_md5.c)
TARGET_LINK_LIBRARIES(md5 a)

# test sha1
ADD_EXECUTABLE(sha1 test_sha1.c)
TARGET_LINK_LIBRARIES(sha1 a)

# test sha256
ADD_EXECUTABLE(sha256 test_sha256.c)
TARGET_LINK_LIBRARIES(sha256 a)

# test sha512
ADD_EXECUTABLE(sha512 test_sha512.c)
TARGET_LINK_LIBRARIES(sha512 a)

# test sha3
ADD_EXECUTABLE(sha3 test_sha3.c)
TARGET_LINK_LIBRARIES(sha3 a)
