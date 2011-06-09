# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Maoni)

find_package(Boost NO_MODULE)
include("${Boost_USE_FILE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
  add_definitions(
    /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS)
endif(MSVC)

if(NOT WIN32)
  # 64bit Linux needs this
  add_definitions(-fPIC)
endif(NOT WIN32)


list(APPEND CMAKE_MODULE_PATH ${Maoni_SOURCE_DIR}/CMake)

include_directories(BEFORE SYSTEM include)
install(DIRECTORY include/Maoni DESTINATION include COMPONENT dev)
install(FILES include/Maoni.hpp DESTINATION include COMPONENT dev)

option(MAONI_SKIP_EQUALIZER "Do not build libMaoniEq" ON)
option(MAONI_SKIP_ICET "Do not build libMaoniIceT" ON)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(examples)

set(CPACK_PACKAGE_NAME "libMaoni")
set(CPACK_PACKAGE_VENDOR "http://github.com/purpleKarrot/libMaoni")
set(CPACK_PACKAGE_CONTACT "Daniel Pfeifer <daniel@pfeifer-mail.de>")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${Maoni_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "common viewing framework")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 8)
set(CPACK_PACKAGE_VERSION_PATCH 15)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Maoni")

set(CPACK_RESOURCE_FILE_LICENSE ${Maoni_SOURCE_DIR}/COPYING)

set(CPACK_COMPONENTS_ALL dev doc bin dbg)

set(CPACK_COMPONENT_DEV_DEB_PACKAGE libmaoni-dev)
set(CPACK_COMPONENT_DEV_DISPLAY_NAME "Headers and Libraries")

set(CPACK_COMPONENT_DOC_DEB_PACKAGE libmaoni-doc)
set(CPACK_COMPONENT_DOC_DISPLAY_NAME "Documentation")

set(CPACK_COMPONENT_BIN_DEB_PACKAGE libmaoni)
set(CPACK_COMPONENT_BIN_DISPLAY_NAME "Runtime")

set(CPACK_COMPONENT_DBG_DEB_PACKAGE libmaoni-dbg)
set(CPACK_COMPONENT_DBG_DISPLAY_NAME "Debug")

set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/src/Icons/stanford-bunny.ico")

set(CPACK_DEBIAN_BUILD_DEPENDS
  boost-cmake
  libboost-compatibility-dev
  libboost-serialization-dev
  libboost-iostreams-dev
  libqglviewer-qt4-dev
  libglew1.5-dev
  )

set(CPACK_SOURCE_IGNORE_FILES "${Maoni_BINARY_DIR}/;/\\\\.git")

include(CPack)
include(BoostDebian)
