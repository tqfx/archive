include(UseJava)

get_filename_component(JAVA_BINDIR "${Java_JAVA_EXECUTABLE}" DIRECTORY)
get_filename_component(JAVA_HMOE "${JAVA_BINDIR}" DIRECTORY)
set(JAVA_LIBDIR "${JAVA_HMOE}/lib")

add_jar(jar-a
  SOURCES liba/a.java
  ENTRY_POINT a OUTPUT_NAME a
  GENERATE_NATIVE_HEADERS jar-native-a
)
install_jar(jar-a ${CMAKE_INSTALL_LIBDIR}/java)

add_library(jni-a SHARED src/a.c)
set_target_properties(jni-a PROPERTIES OUTPUT_NAME a)
get_target_property(A_SHARED a POSITION_INDEPENDENT_CODE)
target_link_libraries(jni-a PRIVATE jar-native-a
  $<IF:$<BOOL:${A_SHARED}>,a-static,a>
)
target_library_options(jni-a)

add_jar(jar-aa
  SOURCES liba/aa.java
  ENTRY_POINT aa OUTPUT_NAME aa
  GENERATE_NATIVE_HEADERS jar-native-aa
)
install_jar(jar-aa ${CMAKE_INSTALL_LIBDIR}/java)

add_library(jni-aa SHARED src/aa.cpp)
set_target_properties(jni-aa PROPERTIES OUTPUT_NAME aa)
get_target_property(A_SHARED aa POSITION_INDEPENDENT_CODE)
target_link_libraries(jni-aa PRIVATE jar-native-aa
  $<IF:$<BOOL:${A_SHARED}>,aa-static,aa>
)
target_library_options(jni-aa)

set_target_properties(jni-a jni-aa PROPERTIES DEFINE_SYMBOL A_EXPORTS)

install(TARGETS jni-a jni-aa EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)
install_jar_exports(TARGETS jni-a jni-aa
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

if(NOT ENABLE_SANITIZE)
  include(test.cmake)
endif()
