set(JAVA_LIBRARY_PATH -Djava.library.path=)
set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} ${JAVA_LIBRARY_PATH})

add_jar(test-jar-a
  SOURCES liba/a.java test/aTest.java
  INCLUDE_JARS a-jar
  OUTPUT_NAME test-a
  ENTRY_POINT aTest
)
add_test(NAME test-jar-a
  COMMAND ${JAVA_EXECUTABLE} -jar test-a.jar
)

add_jar(test-jar-ax
  SOURCES liba/ax.java test/axTest.java
  INCLUDE_JARS ax-jar
  OUTPUT_NAME test-ax
  ENTRY_POINT axTest
)
add_test(NAME test-jar-ax
  COMMAND ${JAVA_EXECUTABLE} -jar test-ax.jar
)
