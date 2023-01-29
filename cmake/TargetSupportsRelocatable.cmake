function(TARGET_SUPPORTS_RELOCATABLE)
  set(CMAKETMP ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp)
  get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
  foreach(lang C ${ENABLED_LANGUAGES})
    if(CMAKE_${lang}_COMPILER)
      set(CMAKE_COMPILER ${CMAKE_${lang}_COMPILER})
      break()
    endif()
  endforeach()
  if(NOT CMAKE_COMPILER)
    return()
  endif()
  file(WRITE ${CMAKETMP}/object.c "")
  execute_process(COMMAND ${CMAKE_COMPILER} -nostdlib -o object.o -r object.c
    WORKING_DIRECTORY ${CMAKETMP} ERROR_QUIET OUTPUT_QUIET RESULT_VARIABLE result
  )
  file(REMOVE ${CMAKETMP}/object.o ${CMAKETMP}/object.c)
  if(${result} EQUAL 0)
    set(TARGET_SUPPORTS_RELOCATABLE 1 CACHE INTERNAL "")
  else()
    set(TARGET_SUPPORTS_RELOCATABLE 0 CACHE INTERNAL "")
  endif()
endfunction()
if(NOT DEFINED TARGET_SUPPORTS_RELOCATABLE)
  TARGET_SUPPORTS_RELOCATABLE()
endif()
