cmake_minimum_required(VERSION 3.10)

# test notefreqs
add_executable (test_notefreqs test_notefreqs.c)
target_link_libraries (test_notefreqs a)

# test polynomial
add_executable (test_polynomial test_polynomial.c)
target_link_libraries (test_polynomial a)
