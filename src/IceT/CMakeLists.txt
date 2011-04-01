# Copyright (c) 2009-2011 Daniel Pfeifer, University of Zurich

find_package(MPI)
include_directories("${MPI_INCLUDE_PATH}")

find_package(Boost REQUIRED COMPONENTS mpi openmpi NO_MODULE)
include("${Boost_USE_FILE}")

include(BoostExtract)

set(ICET_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/IceT-1-0-0)
boost_extract(
  ${CMAKE_CURRENT_SOURCE_DIR}/IceT-1-0-0.tar.gz
  ${ICET_SOURCE_DIR}
  )


set(ICET_INSTALL_NO_DEVELOPMENT ON)
set(ICET_INSTALL_NO_LIBRARIES   ON)

# Set the current ICE-T version.
SET(ICET_MAJOR_VERSION 1)
SET(ICET_MINOR_VERSION 0)
SET(ICET_PATCH_VERSION 0)
SET(ICET_VERSION "${ICET_MAJOR_VERSION}.${ICET_MINOR_VERSION}.${ICET_PATCH_VERSION}")

# Configure data type sizes.
INCLUDE (CheckTypeSize)
CHECK_TYPE_SIZE(char        ICET_SIZEOF_CHAR)
CHECK_TYPE_SIZE(short       ICET_SIZEOF_SHORT)
CHECK_TYPE_SIZE(int         ICET_SIZEOF_INT)
CHECK_TYPE_SIZE(long        ICET_SIZEOF_LONG)
CHECK_TYPE_SIZE("long long" ICET_SIZEOF_LONG_LONG)
CHECK_TYPE_SIZE(__int64     ICET_SIZEOF___INT64)
CHECK_TYPE_SIZE(float       ICET_SIZEOF_FLOAT)
CHECK_TYPE_SIZE(double      ICET_SIZEOF_DOUBLE)
CHECK_TYPE_SIZE("void*"     ICET_SIZEOF_VOID_P)

CONFIGURE_FILE(
  ${ICET_SOURCE_DIR}/include/GL/ice-t_config.h.in
  ${ICET_SOURCE_DIR}/include/GL/ice-t_config.h)

include_directories(${ICET_SOURCE_DIR}/include/)

add_subdirectory(${ICET_SOURCE_DIR} ${ICET_SOURCE_DIR}/build)
set(ICET_LIBRARIES icet icet_mpi icet_strategies)


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
