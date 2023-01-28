get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)

foreach(lang ${ENABLED_LANGUAGES})
  set(CMAKE_${lang}_ARCHIVE_APPEND "<CMAKE_${lang}_COMPILER> -o <TARGET> -r <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_APPEND_IPO "<CMAKE_${lang}_COMPILER> -o <TARGET> -r <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_CREATE "<CMAKE_${lang}_COMPILER> -o <TARGET> -r <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_CREATE_IPO "<CMAKE_${lang}_COMPILER> -o <TARGET> -r <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_FINISH "")
  set(CMAKE_${lang}_ARCHIVE_FINISH_IPO "")
endforeach()

set(CMAKE_STATIC_LIBRARY_SUFFIX .o)
add_library(aobj STATIC $<TARGET_OBJECTS:a>)
set_property(TARGET aobj PROPERTY OUTPUT_NAME a)
add_library_properties(aobj INTERFACE alib INTERFACE_)

if(A_HAVE_MIMALLOC_H)
  target_link_libraries(aobj PUBLIC mimalloc-static)
endif()

include(GNUInstallDirs)
install(TARGETS aobj EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
