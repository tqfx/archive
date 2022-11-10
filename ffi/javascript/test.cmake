file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/test/*.js)
add_custom_command(TARGET a-js POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}
)

function(unittest source name)
  add_test(NAME js-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:a-js>
    COMMAND ${NODE_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(lib a)
unittest(pid pid)
unittest(fpid fpid)
unittest(polytrack polytrack)
unittest(version version)
