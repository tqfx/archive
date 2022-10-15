include(UseJava)
get_filename_component(JAVA_BINDIR "${Java_JAVA_EXECUTABLE}" DIRECTORY)
get_filename_component(JAVA_HMOE "${JAVA_BINDIR}" DIRECTORY)
set(JAVA_LIBDIR "${JAVA_HMOE}/lib")

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

file(GLOB_RECURSE SOURCES src/${PROJECT_NAME}/*.java)
add_jar(a-jar
  SOURCES ${SOURCES}
  ENTRY_POINT a OUTPUT_NAME a
  GENERATE_NATIVE_HEADERS jar-native-a
)
install_jar(a-jar ${CMAKE_INSTALL_LIBDIR}/java)

if(ENABLE_JAVADOC)
  create_javadoc(${PROJECT_NAME} FILES ${SOURCES} INSTALLPATH ${CMAKE_INSTALL_DATADIR}/javadoc)
endif()

file(GLOB_RECURSE SOURCES src/*.[ch] src/*.[chm]pp)
add_library(a-jni SHARED ${SOURCES} $<TARGET_OBJECTS:a>)
set_target_properties(a-jni PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_compile_definitions(a-jni PRIVATE $<TARGET_PROPERTY:a,INTERFACE_COMPILE_DEFINITIONS>)
target_include_directories(a-jni PRIVATE $<TARGET_PROPERTY:a,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(a-jni PRIVATE jar-native-a)
target_library_options(a-jni)

install(TARGETS a-jni EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)
install_jar_exports(TARGETS a-jni
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

if(NOT ENABLE_SANITIZE AND BUILD_TESTING)
  include(test.cmake)
endif()
