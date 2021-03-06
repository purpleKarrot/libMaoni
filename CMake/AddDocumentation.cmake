##
# Copyright (c) 2009-2011 Daniel Pfeifer, University of Zurich
##

include(CMakeParseArguments)

# Transform Quickbook into BoostBook XML
function(add_documentation input)
  cmake_parse_arguments(DOC "" "" "IMAGES" ${ARGN})

  file(COPY
      "${Boost_RESOURCE_PATH}/images"
      "${Boost_RESOURCE_PATH}/boost.css"
    DESTINATION
      "${CMAKE_CURRENT_BINARY_DIR}/html/"
    )

  # copy images into different locations... quick and dirty...
  file(COPY ${DOC_IMAGES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/html)
  file(COPY ${DOC_IMAGES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)
  file(COPY ${DOC_IMAGES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/html/images)

  set(qbk "${CMAKE_CURRENT_BINARY_DIR}/libMaoni.qbk")
  set(xml "${CMAKE_CURRENT_BINARY_DIR}/libMaoni.xml")
  set(dbk "${CMAKE_CURRENT_BINARY_DIR}/libMaoni.docbook")
  set(doc "${CMAKE_CURRENT_BINARY_DIR}/html/index.html")

  add_custom_command(OUTPUT ${qbk}
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${input}" ${qbk}
    DEPENDS ${input}
    )

  add_custom_command(OUTPUT ${xml}
    COMMAND $<TARGET_FILE:${BOOST_NAMESPACE}quickbook>
            --input-file ${qbk}
            --include-path "${CMAKE_CURRENT_SOURCE_DIR}"
            --output-file ${xml}
    DEPENDS ${qbk} ${DOC_UNPARSED_ARGUMENTS}
    )

  xsltproc("${dbk}" "${BOOSTBOOK_XSL_DIR}/docbook.xsl" "${xml}"
    DEPENDS ${xml} ${DOC_UNPARSED_ARGUMENTS}
    CATALOG "${BOOSTBOOK_CATALOG}"
    )

  xsltproc("${doc}" "${Boost_RESOURCE_PATH}/docbook-xsl/xhtml.xsl" "${dbk}"
    CATALOG "${BOOSTBOOK_CATALOG}"
    )

  add_custom_target(documentation DEPENDS "${doc}")

  install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/"
    DESTINATION "share/doc/Maoni"
    COMPONENT "doc"
    CONFIGURATIONS Release
    )
endfunction(add_documentation)
