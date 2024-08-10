if(__ok_library)
  return()
endif()
set(__ok_library INCLUDED)

macro(ok_library LIBRARY_NAME_ARG)

add_library(${LIBRARY_NAME_ARG} ${ARGN})

target_include_directories(${LIBRARY_NAME_ARG} PUBLIC .)

endmacro()

macro(ok_executable EXECUTABLE_NAME_ARG)

add_executable(${EXECUTABLE_NAME_ARG} ${ARGN})

endmacro()
