get_filename_component(WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(WORKING_DIRECTORY ${WORKING_DIRECTORY} DIRECTORY)

function(unit_test target)
  add_test(NAME test-py-${target} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/${target}.py ${ARGN}
  )
endfunction()

unit_test(a)

unit_test(aa)
