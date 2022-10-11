if(ENABLE_WARNINGS)
  include(cmake/warnings.cmake)
endif()

set(CMAKE_SHARED_LIBRARY_PREFIX lib)
find_program(LDOC_EXECUTABLE NAMES ldoc)
find_program(LUA_EXECUTABLE NAMES lua
  lua${LUA_VERSION_MAJOR}${LUA_VERSION_MINOR}
  lua${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  lua-${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  lua.${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  HINTS ENV LUA_DIR
)

if(LUA_VERSION_MAJOR AND LUA_VERSION_MINOR)
  set(LUA_VERSION ${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR})
endif()

file(GLOB_RECURSE SOURCES src/*.[ch] src/*.[chm]pp)
add_library(a-lua SHARED ${SOURCES} $<TARGET_PROPERTY:a,SOURCES>)
set_target_properties(a-lua PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_include_directories(a-lua PRIVATE $<TARGET_PROPERTY:a,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(a-lua PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(a-lua PRIVATE ${LUA_LIBRARIES})
target_library_options(a-lua)

install(TARGETS a-lua
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/lua/${LUA_VERSION}
)

function(create_ldoc target)
  # https://stevedonovan.github.io/ldoc/manual/doc.md.html
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.ld
    ${CMAKE_CURRENT_BINARY_DIR}/LDoc.${target}
    @ONLY
  )
  add_custom_target(${target}
    COMMAND ${LDOC_EXECUTABLE} -c ${CMAKE_CURRENT_BINARY_DIR}/LDoc.${target} ${ARGN}
    COMMENT "Generate API documentation for ${target}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
endfunction()

if(ENABLE_LDOC AND LDOC_EXECUTABLE)
  create_ldoc(a-ldoc -f markdown ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

if(NOT LUA_FOUND OR NOT ENABLE_SANITIZE)
  include(test.cmake)
endif()
