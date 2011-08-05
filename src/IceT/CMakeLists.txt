# Copyright (c) 2009-2011 Daniel Pfeifer, University of Zurich

find_package(IceT REQUIRED NO_MODULE)
include_directories(${IceT_INCLUDE_DIRS})

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})

find_package(Boost REQUIRED COMPONENTS mpi NO_MODULE)
include("${Boost_USE_FILE}")

qt4_wrap_cpp(MAONI_ICET_MOC
  TilesWidget.hpp
  )

add_library(MaoniIceT SHARED
  ${MAONI_VERSION_RC}
  ${MAONI_ICET_MOC}
  FrameData.cpp
  main.cpp
  RenderWidget.cpp
  TilesWidget.cpp
  )

target_link_libraries(MaoniIceT
  ${MAONI_LIBRARIES}
  ${MPI_LIBRARIES}
  ${ICET_LIBRARIES}
  )

boost_link_libraries(MaoniIceT
  openmpi
  )
