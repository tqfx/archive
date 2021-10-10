# test math
ADD_EXECUTABLE(math test_math.c)
TARGET_LINK_LIBRARIES(math a)

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

# test rmd
ADD_EXECUTABLE(rmd test_rmd.c)
TARGET_LINK_LIBRARIES(rmd a)

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

# test tiger
ADD_EXECUTABLE(tiger test_tiger.c)
TARGET_LINK_LIBRARIES(tiger a)

# test whirl
ADD_EXECUTABLE(whirl test_whirl.c)
TARGET_LINK_LIBRARIES(whirl a)

# test blake2s
ADD_EXECUTABLE(blake2s test_blake2s.c)
TARGET_LINK_LIBRARIES(blake2s a)

IF("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  TARGET_LINK_LIBRARIES(math m)

ENDIF("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
      "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
      "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
      "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
