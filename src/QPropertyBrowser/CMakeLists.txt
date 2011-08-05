# Copyright (c) 2010-2011 Daniel Pfeifer, University of Zurich

include(BoostExtract)
include(BoostForwardFile)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/browser
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext
  )

# http://get.qt.nokia.com/qt/solutions/lgpl/qtpropertybrowser-2.5_1-opensource.tar.gz
boost_extract(browser
  ${CMAKE_CURRENT_SOURCE_DIR}/qtpropertybrowser-2.5_1-opensource.tar.gz
  )

# http://doc.trolltech.com/qq/qq18-propertybrowser-code.zip
boost_extract(browser-ext
  ${CMAKE_CURRENT_SOURCE_DIR}/qq18-propertybrowser-extension.tar.gz
  )

set(QT_PROPERTY_BROWSER_SRC
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtbuttonpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qteditorfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtgroupboxpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtpropertybrowserutils.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtpropertymanager.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qttreepropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtvariantproperty.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext/fileedit.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext/fileeditfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext/filepathmanager.cpp
  qvector2dpropertymanager.cpp
  qvector3dpropertymanager.cpp
  qvector4dpropertymanager.cpp
  )

qt4_wrap_cpp(QT_PROPERTY_BROWSER_MOC
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtpropertybrowserutils_p.h
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext/fileedit.h
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext/fileeditfactory.h
  ${CMAKE_CURRENT_BINARY_DIR}/browser-ext/filepathmanager.h
  )

qt4_add_resources(QT_PROPERTY_BROWSER_RCC
  ${CMAKE_CURRENT_BINARY_DIR}/browser/qtpropertybrowser.qrc
  )

add_library(QtPropertyBrowser STATIC
  ${QT_PROPERTY_BROWSER_SRC}
  ${QT_PROPERTY_BROWSER_RCC}
  ${QT_PROPERTY_BROWSER_MOC}
  )

##############################################################

MACRO(ADD_COPY_ONLY file)
  set(input  ${CMAKE_CURRENT_SOURCE_DIR}/${file})
  set(output ${CMAKE_CURRENT_BINARY_DIR}/${file})
  add_custom_command(OUTPUT ${output}
    COMMAND ${CMAKE_COMMAND} -E copy ${input} ${output}
    DEPENDS ${input})
ENDMACRO(ADD_COPY_ONLY file)

MACRO(QT4_MOC infile outfile)
  set(input  ${CMAKE_CURRENT_BINARY_DIR}/${infile})
  set(output ${CMAKE_CURRENT_BINARY_DIR}/${outfile})
  add_custom_command(OUTPUT ${output}
    COMMAND ${QT_MOC_EXECUTABLE} -o ${output} ${input}
    DEPENDS ${input})
  list(APPEND MOC_OUTPUT_LIST ${output})
ENDMACRO(QT4_MOC)

ADD_COPY_ONLY(qvector2dpropertymanager.h)
ADD_COPY_ONLY(qvector3dpropertymanager.h)
ADD_COPY_ONLY(qvector4dpropertymanager.h)

set(MOC_OUTPUT_LIST)
QT4_MOC(browser/qtbuttonpropertybrowser.h   browser/moc_qtbuttonpropertybrowser.cpp)
QT4_MOC(browser/qteditorfactory.h           browser/moc_qteditorfactory.cpp)
QT4_MOC(browser/qteditorfactory.cpp         browser/qteditorfactory.moc)
QT4_MOC(browser/qtgroupboxpropertybrowser.h browser/moc_qtgroupboxpropertybrowser.cpp)
QT4_MOC(browser/qtpropertybrowser.h         browser/moc_qtpropertybrowser.cpp)
QT4_MOC(browser/qtpropertymanager.h         browser/moc_qtpropertymanager.cpp)
QT4_MOC(browser/qtpropertymanager.cpp       browser/qtpropertymanager.moc)
QT4_MOC(browser/qttreepropertybrowser.h     browser/moc_qttreepropertybrowser.cpp)
QT4_MOC(browser/qttreepropertybrowser.cpp   browser/qttreepropertybrowser.moc)
QT4_MOC(browser/qtvariantproperty.h         browser/moc_qtvariantproperty.cpp)
QT4_MOC(qvector2dpropertymanager.h          moc_qvector2dpropertymanager.cpp)
QT4_MOC(qvector3dpropertymanager.h          moc_qvector3dpropertymanager.cpp)
QT4_MOC(qvector4dpropertymanager.h          moc_qvector4dpropertymanager.cpp)

add_custom_target(QtPropertyBrowser_moc DEPENDS ${MOC_OUTPUT_LIST})
add_dependencies(QtPropertyBrowser QtPropertyBrowser_moc)
