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

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/QGLViewer/qglviewer/QGLViewer
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser/browser
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser/browser-ext
  )

add_definitions(
  -DBOOST_ALL_NO_LIB
  -DQGLVIEWER_STATIC
  )


add_subdirectory(Common)
add_subdirectory(QGLViewer)
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
add_subdirectory(IceT)

add_library(Maoni SHARED Maoni.cpp ${MAONI_VERSION_RC})
target_link_libraries(Maoni ${MAONI_LIBRARIES})
boost_link_libraries(Maoni serialization)

add_library(MaoniMain STATIC main.cpp)
