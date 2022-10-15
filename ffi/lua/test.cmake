function(unittest target)
  add_test(NAME lua-${target} WORKING_DIRECTORY $<TARGET_FILE_DIR:a-lua>
    COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/${target}.lua
  )
endfunction()

unittest(lib)
unittest(mf)
unittest(tf)
unittest(pid)
unittest(fpid)
unittest(polytrack)
unittest(version)
