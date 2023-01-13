function(unittest source name)
  add_test(NAME lua-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:alua>
    COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/${source}.lua ${ARGN}
  )
endfunction()

unittest(lib a)
unittest(mf mf)
unittest(tf tf)
unittest(pid pid)
unittest(fpid fpid)
unittest(complex complex)
unittest(polytrack polytrack)
unittest(version version)
