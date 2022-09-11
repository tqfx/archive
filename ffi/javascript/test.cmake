function(unittest target)
  add_test(NAME js-${target} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${NODE_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/${target}.js ${ARGN}
  )
endfunction()

unittest(pid)
unittest(version)
