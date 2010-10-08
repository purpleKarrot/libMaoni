# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Maoni)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
  add_definitions(
    /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS)
endif(MSVC)

if(NOT WIN32)
  # 64bit Linux needs this
  add_definitions(-fPIC)
endif(NOT WIN32)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CToolBox)
include(DailyVersion)

include_directories(BEFORE SYSTEM include)
install(DIRECTORY include/Maoni DESTINATION include COMPONENT dev)
install(FILES include/Maoni.hpp DESTINATION include COMPONENT dev)

option(MAONI_SKIP_EQUALIZER "Do not build libMaoniEq" OFF)
option(MAONI_SKIP_ICET "Do not build libMaoniIceT" OFF)

add_subdirectory(src)
add_subdirectory(examples)
add_custom_target(check)


# Building of Documentation is tested on Linux only
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(THIS_PROJECT_NAME libMaoni)
  include(AddReference)
  include(AddDocumentation)
  add_subdirectory(doc EXCLUDE_FROM_ALL)
endif(CMAKE_SYSTEM_NAME STREQUAL Linux)

SET(CPACK_SOURCE_IGNORE_FILES "/[.][^/]*;${CMAKE_BINARY_DIR}/")

set(CPACK_PACKAGE_NAME "libMaoni")
set(CPACK_PACKAGE_VENDOR "http://github.com/purpleKarrot/libMaoni")
set(CPACK_PACKAGE_CONTACT "Daniel Pfeifer <daniel@pfeifer-mail.de>")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "common viewing framework")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Maoni")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)

set(CPACK_COMPONENTS_ALL dev examples)

set(CPACK_COMPONENT_DEV_DISPLAY_NAME "Headers and Libraries")
set(CPACK_COMPONENT_DEV_DESCRIPTION
  "Header Files and Developer Libraries")

set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION
  "Example source code and model files")

set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/src/Icons/stanford-bunny.ico")

set(CPACK_DEBIAN_BUILD_DEPENDS
  libqt4-dev
  libqt4-opengl-dev
  libboost-all-dev
  libglew1.5-dev
  equalizer
  doxygen
  xsltproc
  )

set(DPUT_HOST "ppa:purplekarrot/ppa")

include(CPack)
include(UploadPPA)
