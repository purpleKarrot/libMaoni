# Copyright (c) 2010-2011 Daniel Pfeifer, University of Zurich

include(BoostExtract)
include(BoostForwardFile)

boost_extract(qglviewer DOWNLOAD
  http://www.libqglviewer.com/src/libQGLViewer-2.3.10.tar.gz
  259538c7036b4ae5fe3ed5d4299c8d31
  )

set(qglviewer_dir "${CMAKE_CURRENT_BINARY_DIR}/qglviewer/QGLViewer")

add_definitions(-DNO_VECTORIAL_RENDER)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

qt4_wrap_ui(QGLVIEWER_UI
  ${qglviewer_dir}/ImageInterface.Qt4.ui
  )

boost_forward_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ui_ImageInterface.h"
  "${CMAKE_CURRENT_BINARY_DIR}/ui_ImageInterface.Qt4.h"
  )

qt4_wrap_cpp(QGLVIEWER_MOC
  ${qglviewer_dir}/camera.h
  ${qglviewer_dir}/frame.h
  ${qglviewer_dir}/keyFrameInterpolator.h
  ${qglviewer_dir}/manipulatedCameraFrame.h
  ${qglviewer_dir}/manipulatedFrame.h
  ${qglviewer_dir}/qglviewer.h
  )

add_library(QGLViewer
  ${QGLVIEWER_UI}
  ${QGLVIEWER_MOC}
  ${qglviewer_dir}/camera.cpp
  ${qglviewer_dir}/constraint.cpp
  ${qglviewer_dir}/frame.cpp
  ${qglviewer_dir}/keyFrameInterpolator.cpp
  ${qglviewer_dir}/manipulatedCameraFrame.cpp
  ${qglviewer_dir}/manipulatedFrame.cpp
  ${qglviewer_dir}/mouseGrabber.cpp
  ${qglviewer_dir}/qglviewer.cpp
  ${qglviewer_dir}/quaternion.cpp
  ${qglviewer_dir}/saveSnapshot.cpp
  ${qglviewer_dir}/vec.cpp
  )
