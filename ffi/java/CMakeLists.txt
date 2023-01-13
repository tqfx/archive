# https://cmake.org/cmake/help/latest/module/UseJava.html
include(UseJava)

file(GLOB_RECURSE SOURCES src/${PROJECT_NAME}/*.java)
add_jar(ajar GENERATE_NATIVE_HEADERS jar-native-a
  ENTRY_POINT a OUTPUT_NAME a SOURCES ${SOURCES}
)
install_jar(ajar ${CMAKE_INSTALL_LIBDIR}/java)

option(LIBA_JAVADOC "Enable/Disable ffi javadoc" 0)

if(LIBA_JAVADOC)
  create_javadoc(${PROJECT_NAME} FILES ${SOURCES}
    INSTALLPATH ${CMAKE_INSTALL_DATADIR}/javadoc
  )
endif()

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX)
endif()

file_scaner(SOURCES RECURSE src)
add_library(ajni SHARED ${SOURCES} $<TARGET_OBJECTS:a>)
set_target_properties(ajni PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_compile_definitions(ajni PRIVATE $<TARGET_PROPERTY:alib,COMPILE_DEFINITIONS>)
target_include_directories(ajni PRIVATE $<TARGET_PROPERTY:alib,INCLUDE_DIRECTORIES>)
target_link_libraries(ajni PRIVATE $<TARGET_PROPERTY:alib,LINK_LIBRARIES>)
target_link_libraries(ajni PRIVATE jar-native-a)
set_library_options(ajni)

install(TARGETS ajni
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)

execute_process(COMMAND ${Java_JAVA_EXECUTABLE} -version
  OUTPUT_VARIABLE version ERROR_VARIABLE version
)
string(FIND "${version}" "64-Bit" index)

if(${index} GREATER -1)
  set(JAVA_SIZEOF_VOID_P 8) # 64
else()
  set(JAVA_SIZEOF_VOID_P 4) # 32
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL JAVA_SIZEOF_VOID_P AND BUILD_TESTING)
  include(test.cmake)
endif()
