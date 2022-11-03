set(CMAKE_C_CREATE_PREPROCESSED_SOURCE "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -E <SOURCE> > <PREPROCESSED_SOURCE>")
set(CMAKE_C_CREATE_ASSEMBLY_SOURCE "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -S <SOURCE> -o <ASSEMBLY_SOURCE>")
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> -ar qc <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_APPEND "<CMAKE_AR> -ar q <TARGET> <LINK_FLAGS> <OBJECTS>")
cmake_host_system_information(RESULT OS_PLATFORM QUERY OS_PLATFORM)
cmake_host_system_information(RESULT OS_NAME QUERY OS_NAME)
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT -O2)
set(CMAKE_C_FLAGS_MINSIZEREL_INIT -Os)
set(CMAKE_C_FLAGS_RELEASE_INIT -O2)
find_program(CMAKE_C_COMPILER tcc)
find_program(CMAKE_AR tcc)
set(CMAKE_CXX_COMPILER 0)

if(ANDROID)
  string(TOLOWER ${OS_PLATFORM}-${OS_NAME}-android CMAKE_LIBRARY_ARCHITECTURE)
elseif(UNIX)
  string(TOLOWER ${OS_PLATFORM}-${OS_NAME}-gnu CMAKE_LIBRARY_ARCHITECTURE)
endif()
