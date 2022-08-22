function(doxygen_add_docs target)
  string(REPLACE ";" " " DOXYGEN_EXCLUDE_SYMBOLS "${DOXYGEN_EXCLUDE_SYMBOLS}")
  string(REPLACE ";" " " DOXYGEN_PREDEFINED "${DOXYGEN_PREDEFINED}")

  foreach(v ${ARGN})
    string(STRIP "${DOXYGEN_INPUT} ${v}" DOXYGEN_INPUT)
  endforeach()

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.${target}
    @ONLY
  )

  add_custom_target(${target}
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.${target}
    COMMENT "Generate API documentation for ${target}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
endfunction()
