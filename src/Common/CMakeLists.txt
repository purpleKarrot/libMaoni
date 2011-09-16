# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

qt4_wrap_cpp(COMMON_MOC
  AlgorithmWidget.hpp
  MainWindow.hpp
  RenderWidget.hpp
  TextOutput.hpp
  )

#qt4_add_resources(COMMON_QRC
#  Resources.qrc
#  )

add_library(Common STATIC
  ${COMMON_MOC}
# ${COMMON_QRC}
  AlgorithmWidget.cpp
  Gears.c
  FrameData.cpp
  MainWindow.cpp
  Path.cpp
  RenderWidget.cpp
  ShaderProgram.cpp
  Texture.cpp
  )

add_dependencies(Common QtPropertyBrowser)
