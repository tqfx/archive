# Set the compiler C standard
macro(set_c_standard var)
  set(CMAKE_C_EXTENSIONS 0)
  set(CMAKE_C_STANDARD ${var})
  set(CMAKE_C_STANDARD_REQUIRED 1)
endmacro()

# Set the compiler C++ standard
macro(set_cxx_standard var)
  set(CMAKE_CXX_EXTENSIONS 0)
  set(CMAKE_CXX_STANDARD ${var})
  set(CMAKE_CXX_STANDARD_REQUIRED 1)
endmacro()

# default C standard
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

if(NOT CMAKE_C_EXTENSIONS)
  set(CMAKE_C_EXTENSIONS 0)
endif()

if(NOT CMAKE_C_STANDARD_REQUIRED)
  set(CMAKE_C_STANDARD_REQUIRED 0)
endif()

# default C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS 0)
endif()

if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED 0)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
  string_append(CMAKE_C_FLAGS -std=c${CMAKE_C_STANDARD})
endif()
