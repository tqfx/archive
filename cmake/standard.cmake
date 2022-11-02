# Set the compiler C standard
macro(set_c_standard variable)
  set(CMAKE_C_EXTENSIONS OFF)
  set(CMAKE_C_STANDARD ${variable})
  set(CMAKE_C_STANDARD_REQUIRED ON)
endmacro()

# Set the compiler C++ standard
macro(set_cxx_standard variable)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD ${variable})
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endmacro()

# default C standard
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

if(NOT CMAKE_C_EXTENSIONS)
  set(CMAKE_C_EXTENSIONS OFF)
endif()

if(NOT CMAKE_C_STANDARD_REQUIRED)
  set(CMAKE_C_STANDARD_REQUIRED OFF)
endif()

# default C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED OFF)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
  string_append(CMAKE_C_FLAGS -std=c${CMAKE_C_STANDARD})
endif()
