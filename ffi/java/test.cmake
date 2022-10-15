set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)
file(GLOB_RECURSE SOURCES src/${PROJECT_NAME}/*.java)

function(building target source)
  add_jar(jar-${target} INCLUDE_JARS a-jar
    SOURCES ${SOURCES} test/${source}.java
    ENTRY_POINT ${source}
    OUTPUT_NAME ${source}
  )
endfunction()

function(unittest target source)
  add_test(NAME jar-${target} WORKING_DIRECTORY $<TARGET_FILE_DIR:a-jni>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source}.jar ${ARGN}
  )
endfunction()

building(test test)
unittest(lib test)

building(test-mf test_mf)
unittest(mf test_mf)

building(test-tf test_tf)
unittest(tf test_tf)

building(test-pid test_pid)
unittest(pid test_pid)

building(test-fpid test_fpid)
unittest(fpid test_fpid)

building(test-polytrack3 test_polytrack3)
unittest(polytrack3 test_polytrack3)

building(test-polytrack5 test_polytrack5)
unittest(polytrack5 test_polytrack5)

building(test-polytrack7 test_polytrack7)
unittest(polytrack7 test_polytrack7)
