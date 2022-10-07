get_filename_component(WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(WORKING_DIRECTORY ${WORKING_DIRECTORY} DIRECTORY)

function(unittest target)
  add_test(NAME py-${target} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/${target}.py ${ARGN}
  )
endfunction()

unittest(a)
