# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

include(CMakeParseArguments)

find_package(Boost REQUIRED)
include_directories(
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/include
  )

add_custom_target(examples)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data)

macro(MAONI_MODULE NAME)
  set(MODULE_SOURCE_PATH ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_source)
  set(MODULE_BINARY_PATH ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_binary)
  set(MODULE_LISTS_FILE ${MODULE_SOURCE_PATH}/CMakeLists.txt)

  cmake_parse_arguments(MODULE "" "" "INCLUDE_DIRECTORIES;SOURCE;DATA" ${ARGN})

  foreach(FILE ${MODULE_DATA})
    file(COPY ${MODULE_PATH}/${FILE}
      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data)
    install(FILES ${MODULE_PATH}/${FILE}
      DESTINATION share/Maoni/data COMPONENT examples)
  endforeach(FILE ${MODULE_DATA})

  set(INCLUDES)
  foreach(DIRECTORY ${MODULE_INCLUDE_DIRECTORIES})
    if(IS_ABSOLUTE ${DIRECTORY})
      set(INCLUDES "${INCLUDES} ${DIRECTORY}")
    else(IS_ABSOLUTE ${DIRECTORY})
      set(INCLUDES "${INCLUDES} ${MODULE_PATH}/${DIRECTORY}")
    endif(IS_ABSOLUTE ${DIRECTORY})
  endforeach(DIRECTORY ${MODULE_INCLUDE_DIRECTORIES})

  file(WRITE ${MODULE_LISTS_FILE} "# ${NAME}\n\n")
  if(INCLUDES)
    file(APPEND ${MODULE_LISTS_FILE} "include_directories(${INCLUDES})\n\n")
  endif(INCLUDES)

  set(SOURCES)
  foreach(FILE ${MODULE_SOURCE})
    install(FILES ${MODULE_PATH}/${FILE}
      DESTINATION share/Maoni/${NAME} COMPONENT examples)
    file(RELATIVE_PATH FILE ${MODULE_SOURCE_PATH} ${MODULE_PATH}/${FILE})
    set(SOURCES "${SOURCES}\n  ${FILE}")
  endforeach(FILE ${MODULE_SOURCE})

  file(APPEND ${MODULE_LISTS_FILE}
    "add_executable(${NAME} EXCLUDE_FROM_ALL ${SOURCES})\n\n"
    "add_dependencies(examples ${NAME})\n"
    "target_link_libraries(${NAME} Maoni MaoniMain)\n"
    )

#  "add_executable(${NAME}_IceT EXCLUDE_FROM_ALL ${SOURCES})\n"
#  "add_dependencies(examples ${NAME}_IceT)\n"
#  "target_link_libraries(${NAME}_IceT MaoniIceT MaoniMain)\n"

  add_subdirectory(${MODULE_SOURCE_PATH} ${MODULE_BINARY_PATH})
endmacro(MAONI_MODULE NAME)

# search all subdirectories for examples
file(GLOB EXAMPLES_SD */Maoni.cmake)

# search workspace for examples
file(GLOB EXAMPLES_WS ${CMAKE_SOURCE_DIR}/../*/Maoni.cmake)

foreach(MODULE ${EXAMPLES_SD} ${EXAMPLES_WS})
  get_filename_component(MODULE_PATH ${MODULE} PATH)
  message(STATUS "Maoni module found at: ${MODULE_PATH}")
  include(${MODULE})
endforeach(MODULE)
