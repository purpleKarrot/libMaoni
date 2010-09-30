# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

include(ParseArguments)

find_package(Boost REQUIRED)
include_directories(
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/include
  )

add_custom_target(examples)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data)

macro(MAONI_MODULE NAME)
  parse_arguments(MODULE "SOURCE;DATA" "" ${ARGN})

  foreach(FILE ${MODULE_DATA})
    file(COPY ${MODULE_PATH}/${FILE}
      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data)
  endforeach(FILE ${MODULE_DATA})

  set(SOURCES)
  foreach(FILE ${MODULE_SOURCE})
    list(APPEND SOURCES ${MODULE_PATH}/${FILE})
  endforeach(FILE ${MODULE_SOURCE})

  add_executable(${NAME} EXCLUDE_FROM_ALL ${SOURCES})
  add_dependencies(examples ${NAME})
  target_link_libraries(${NAME} Maoni MaoniMain)
  
endmacro(MAONI_MODULE NAME)

# search all subdirectories for examples
file(GLOB MODULES */Maoni.cmake)
foreach(MODULE ${MODULES})
  get_filename_component(MODULE_PATH ${MODULE} PATH)
  include(${MODULE})
endforeach(MODULE ${MODULES})
