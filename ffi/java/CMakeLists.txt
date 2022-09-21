include(UseJava)

get_filename_component(JAVA_BINDIR "${Java_JAVA_EXECUTABLE}" DIRECTORY)
get_filename_component(JAVA_HMOE "${JAVA_BINDIR}" DIRECTORY)
set(JAVA_LIBDIR "${JAVA_HMOE}/lib")

add_jar(ac-jar
  SOURCES src/${PROJECT_NAME}/ac.java
  ENTRY_POINT ac OUTPUT_NAME ac
  GENERATE_NATIVE_HEADERS jar-native-ac
)
install_jar(ac-jar ${CMAKE_INSTALL_LIBDIR}/java)

file(GLOB_RECURSE SOURCES src/*.c)
add_library(ac-jni SHARED ${SOURCES} $<TARGET_OBJECTS:ac>)
target_compile_definitions(ac-jni PRIVATE A_REAL_BITS=64)
set_target_properties(ac-jni PROPERTIES OUTPUT_NAME ac)
target_link_libraries(ac-jni PRIVATE jar-native-ac ac)
target_library_options(ac-jni)

add_jar(ax-jar
  SOURCES src/${PROJECT_NAME}/ax.java
  ENTRY_POINT ax OUTPUT_NAME ax
  GENERATE_NATIVE_HEADERS jar-native-ax
)
install_jar(ax-jar ${CMAKE_INSTALL_LIBDIR}/java)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(ax-jni SHARED ${SOURCES} $<TARGET_OBJECTS:ax>)
target_compile_definitions(ax-jni PRIVATE A_REAL_BITS=64)
set_target_properties(ax-jni PROPERTIES OUTPUT_NAME ax)
target_link_libraries(ax-jni PRIVATE jar-native-ax ax)
target_library_options(ax-jni)

set_target_properties(ac-jni ax-jni PROPERTIES DEFINE_SYMBOL A_EXPORTS)

install(TARGETS ac-jni ax-jni EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)
install_jar_exports(TARGETS ac-jni ax-jni
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

if(NOT ENABLE_SANITIZE)
  include(test.cmake)
endif()
