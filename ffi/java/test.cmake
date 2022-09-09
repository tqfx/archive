get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)

function(unittest target source)
  add_test(NAME ${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<${IS_MULTI_CONFIG}:$<CONFIG>>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source} ${ARGN}
  )
endfunction()

unittest(jar-ac acTest.jar)
add_jar(ac-jar-test
  SOURCES test/acTest.java src/${PROJECT_NAME}/ac.java
  INCLUDE_JARS ac-jar
  OUTPUT_NAME acTest
  ENTRY_POINT acTest
)

unittest(jar-ax axTest.jar)
add_jar(ax-jar-test
  SOURCES test/axTest.java src/${PROJECT_NAME}/ax.java
  INCLUDE_JARS ax-jar
  OUTPUT_NAME axTest
  ENTRY_POINT axTest
)
