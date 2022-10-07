get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)

function(unittest target source)
  add_test(NAME ${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source} ${ARGN}
  )
endfunction()

unittest(jar-a aTest.jar)
add_jar(a-jar-test
  SOURCES test/aTest.java src/${PROJECT_NAME}/a.java
  INCLUDE_JARS a-jar
  OUTPUT_NAME aTest
  ENTRY_POINT aTest
)
