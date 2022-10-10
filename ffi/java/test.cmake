get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)
file(GLOB_RECURSE SOURCES src/${PROJECT_NAME}/*.java)

function(building target source)
  add_jar(${target} INCLUDE_JARS a-jar
    SOURCES ${SOURCES} test/${source}.java
    ENTRY_POINT ${source}
    OUTPUT_NAME ${source}
  )
endfunction()

function(unittest target source)
  add_test(NAME ${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source}.jar ${ARGN}
  )
endfunction()

building(jar-test test)
unittest(jar-a test)

building(jar-test-mf test_mf)
unittest(jar-mf test_mf)

building(jar-test-tf test_tf)
unittest(jar-tf test_tf)

building(jar-test-pid test_pid)
unittest(jar-pid test_pid)

building(jar-test-fpid test_fpid)
unittest(jar-fpid test_fpid)

building(jar-test-polytrack3 test_polytrack3)
unittest(jar-polytrack3 test_polytrack3)

building(jar-test-polytrack5 test_polytrack5)
unittest(jar-polytrack5 test_polytrack5)

building(jar-test-polytrack7 test_polytrack7)
unittest(jar-polytrack7 test_polytrack7)
