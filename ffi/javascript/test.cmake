file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/test/*.js)
file(COPY ${SOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

function(unittest source name)
  add_test(NAME js-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:ajs>
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${CMAKE_CURRENT_BINARY_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(lib a)
unittest(pid pid)
unittest(fpid fpid)
unittest(polytrack polytrack)
unittest(version version)
