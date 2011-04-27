##
# Copyright (c) 2009-2011 Daniel Pfeifer, University of Zurich
##

find_package(Boost REQUIRED COMPONENTS serialization NO_MODULE)
include("${Boost_USE_FILE}")

find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui QtOpenGL QtXml)
include("${QT_USE_FILE}")

find_package(OpenGL REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/boost-la.tar.gz
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/include)


find_package(QGLViewer)
if(QGLVIEWER_FOUND)
  include_directories(${QGLVIEWER_INCLUDE_DIR})
  add_library(QGLViewer SHARED IMPORTED)
  set_target_properties(QGLViewer PROPERTIES
    IMPORTED_LOCATION "${QGLVIEWER_LIBRARY}"
    )
else(QGLVIEWER_FOUND)
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/QGLViewer/qglviewer/QGLViewer)
  add_definitions(-DQGLVIEWER_STATIC)
  add_subdirectory(QGLViewer)
endif(QGLVIEWER_FOUND)


include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser/browser
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser/browser-ext
  )

add_subdirectory(Common)
add_subdirectory(QPropertyBrowser)

set(MAONI_LIBRARIES
  Common
  QGLViewer
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )

if(MSVC)
  set(MAONI_VERSION_RC ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif(MSVC)


#add_subdirectory(Equalizer)
#add_subdirectory(IceT)


add_library(Maoni SHARED Maoni.cpp ${MAONI_VERSION_RC})
target_link_libraries(Maoni ${MAONI_LIBRARIES})
boost_link_libraries(Maoni serialization)

add_library(MaoniMain STATIC main.cpp)


install(TARGETS Maoni MaoniMain EXPORT Maoni
  ARCHIVE DESTINATION lib COMPONENT dev
  LIBRARY DESTINATION lib COMPONENT dev
  RUNTIME DESTINATION bin
  )

# install(EXPORT Maoni
#   DESTINATION share/Maoni
#   COMPONENT dev
#   )
