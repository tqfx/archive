include(UseJava)

get_filename_component(JAVA_BINDIR "${Java_JAVA_EXECUTABLE}" DIRECTORY)
get_filename_component(JAVA_HMOE "${JAVA_BINDIR}" DIRECTORY)
set(JAVA_LIBDIR "${JAVA_HMOE}/lib")

add_jar(a-jar
  SOURCES liba/a.java
  ENTRY_POINT a OUTPUT_NAME a
  GENERATE_NATIVE_HEADERS jar-native-a
)
install_jar(a-jar ${CMAKE_INSTALL_LIBDIR}/java)

file(GLOB_RECURSE SOURCES src/*.c)
add_library(a-jni SHARED ${SOURCES} $<TARGET_OBJECTS:a>)
set_target_properties(a-jni PROPERTIES OUTPUT_NAME a)
target_link_libraries(a-jni PRIVATE jar-native-a a)
target_library_options(a-jni)

add_jar(ax-jar
  SOURCES liba/ax.java
  ENTRY_POINT ax OUTPUT_NAME ax
  GENERATE_NATIVE_HEADERS jar-native-ax
)
install_jar(ax-jar ${CMAKE_INSTALL_LIBDIR}/java)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(ax-jni SHARED ${SOURCES} $<TARGET_OBJECTS:ax>)
set_target_properties(ax-jni PROPERTIES OUTPUT_NAME ax)
target_link_libraries(ax-jni PRIVATE jar-native-ax ax)
target_library_options(ax-jni)

set_target_properties(a-jni ax-jni PROPERTIES DEFINE_SYMBOL A_EXPORTS)

install(TARGETS a-jni ax-jni EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)
install_jar_exports(TARGETS a-jni ax-jni
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

if(NOT ENABLE_SANITIZE)
  include(test.cmake)
endif()
