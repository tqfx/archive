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

add_library(a-jni SHARED $<TARGET_OBJECTS:a> src/a.c)
set_target_properties(a-jni PROPERTIES OUTPUT_NAME a)
target_link_libraries(a-jni PRIVATE jar-native-a a)
target_library_options(a-jni)

add_jar(aa-jar
  SOURCES liba/aa.java
  ENTRY_POINT aa OUTPUT_NAME aa
  GENERATE_NATIVE_HEADERS jar-native-aa
)
install_jar(aa-jar ${CMAKE_INSTALL_LIBDIR}/java)

add_library(aa-jni SHARED $<TARGET_OBJECTS:aa> src/aa.cpp)
set_target_properties(aa-jni PROPERTIES OUTPUT_NAME aa)
target_link_libraries(aa-jni PRIVATE jar-native-aa aa)
target_library_options(aa-jni)

set_target_properties(a-jni aa-jni PROPERTIES DEFINE_SYMBOL A_EXPORTS)

install(TARGETS a-jni aa-jni EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)
install_jar_exports(TARGETS a-jni aa-jni
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

if(NOT ENABLE_SANITIZE)
  include(test.cmake)
endif()
