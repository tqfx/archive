set(JAVA_LIBRARY_PATH -Djava.library.path=)
set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} ${JAVA_LIBRARY_PATH})

add_jar(test-jar-a
  SOURCES liba/a.java test/aTest.java
  INCLUDE_JARS jar-a
  OUTPUT_NAME test-a
  ENTRY_POINT aTest
)
add_test(NAME test-jar-a
  COMMAND ${JAVA_EXECUTABLE} -jar test-a.jar
)

add_jar(test-jar-aa
  SOURCES liba/aa.java test/aaTest.java
  INCLUDE_JARS jar-aa
  OUTPUT_NAME test-aa
  ENTRY_POINT aaTest
)
add_test(NAME test-jar-aa
  COMMAND ${JAVA_EXECUTABLE} -jar test-aa.jar
)
