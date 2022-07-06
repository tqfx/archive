include(UseJava)

get_filename_component(JAVA_BIN_DIR "${Java_JAVA_EXECUTABLE}" DIRECTORY)
get_filename_component(JAVA_HMOE "${JAVA_BIN_DIR}" DIRECTORY)
set(JAVA_LIB_DIR "${JAVA_HMOE}/lib")

add_jar(jar-a
  SOURCES liba/a.java
  ENTRY_POINT a OUTPUT_NAME a
  GENERATE_NATIVE_HEADERS jar-native-a
)
install_jar(jar-a share/java)

add_library(jni-a SHARED src/a.c)
set_target_properties(jni-a PROPERTIES
  DEFINE_SYMBOL A_EXPORTS
  OUTPUT_NAME a
)
target_link_libraries(jni-a PRIVATE jar-native-a a)
target_compile_options(jni-a PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang,IntelLLVM>:-Wall -Wextra -Wpedantic>
  $<$<C_COMPILER_ID:MSVC>:/W4 /sdl> $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
)
target_compile_definitions(jni-a PUBLIC A_SHARED)

add_jar(jar-aa
  SOURCES liba/aa.java
  ENTRY_POINT aa OUTPUT_NAME aa
  GENERATE_NATIVE_HEADERS jar-native-aa
)
install_jar(jar-aa share/java)

add_library(jni-aa SHARED src/aa.cpp)
set_target_properties(jni-aa PROPERTIES
  DEFINE_SYMBOL A_EXPORTS
  OUTPUT_NAME aa
)
target_link_libraries(jni-aa PRIVATE jar-native-aa aa)
target_compile_options(jni-aa PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang,IntelLLVM>:-Wall -Wextra -Wpedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /sdl> $<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>
)
target_compile_definitions(jni-aa PUBLIC A_SHARED)

install(TARGETS jni-a jni-aa
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${JAVA_LIB_DIR}
  LIBRARY DESTINATION ${JAVA_LIB_DIR}
  RUNTIME DESTINATION ${JAVA_BIN_DIR}
)
install_jar_exports(TARGETS jni-a jni-aa
  DESTINATION lib/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

if(NOT ENABLE_SANITIZE)
  include(testing.cmake)
endif()
