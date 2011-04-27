
# DEBIAN/control
# debian policy enforce lower case for package name
# Package: (mandatory)
IF(NOT CPACK_DEBIAN_PACKAGE_NAME)
  STRING(TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_DEBIAN_PACKAGE_NAME)
ENDIF(NOT CPACK_DEBIAN_PACKAGE_NAME)

# Section: (recommended)
IF(NOT CPACK_DEBIAN_PACKAGE_SECTION)
  SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
ENDIF(NOT CPACK_DEBIAN_PACKAGE_SECTION)

# Priority: (recommended)
IF(NOT CPACK_DEBIAN_PACKAGE_PRIORITY)
  SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
ENDIF(NOT CPACK_DEBIAN_PACKAGE_PRIORITY)

file(STRINGS ${CPACK_PACKAGE_DESCRIPTION_FILE} DESC_LINES)
foreach(LINE ${DESC_LINES})
  set(DEB_LONG_DESCRIPTION "${DEB_LONG_DESCRIPTION} ${LINE}\n")
endforeach(LINE ${DESC_LINES})

file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/Debian)
set(DEBIAN_SOURCE_DIR ${CMAKE_BINARY_DIR}/Debian/${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-source)
execute_process(COMMAND ${CMAKE_COMMAND} -E
  copy_directory ${CMAKE_SOURCE_DIR} ${DEBIAN_SOURCE_DIR}
  )
execute_process(COMMAND ${CMAKE_COMMAND} -E
  remove_directory ${DEBIAN_SOURCE_DIR}/.git
  )

file(MAKE_DIRECTORY ${DEBIAN_SOURCE_DIR}/debian)

##############################################################################
# debian/control
set(DEBIAN_CONTROL ${DEBIAN_SOURCE_DIR}/debian/control)
file(WRITE ${DEBIAN_CONTROL}
  "Source: ${CPACK_DEBIAN_PACKAGE_NAME}\n"
  "Section: ${CPACK_DEBIAN_PACKAGE_SECTION}\n"
  "Priority: ${CPACK_DEBIAN_PACKAGE_PRIORITY}\n"
  "Maintainer: ${CPACK_PACKAGE_CONTACT}\n"
  "Build-Depends: "
  )

foreach(DEP ${CPACK_DEBIAN_BUILD_DEPENDS})
  file(APPEND ${DEBIAN_CONTROL} "${DEP}, ")
endforeach(DEP ${CPACK_DEBIAN_BUILD_DEPENDS})  

file(APPEND ${DEBIAN_CONTROL} "cmake\n"
  "Standards-Version: 3.8.4\n"
  "Homepage: ${CPACK_PACKAGE_VENDOR}\n"
  "\n"
  "Package: ${CPACK_DEBIAN_PACKAGE_NAME}\n"
  "Architecture: any\n"
  "Depends: ${CPACK_DEBIAN_PACKAGE_DEPENDS}\n"
  "Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}\n"
  "${DEB_LONG_DESCRIPTION}"
  )

foreach(COMPONENT ${CPACK_COMPONENTS_ALL})
  string(TOUPPER ${COMPONENT} UPPER_COMPONENT)
  file(APPEND ${DEBIAN_CONTROL} "\n"
    "Package: ${CPACK_DEBIAN_PACKAGE_NAME}-${COMPONENT}\n"
    "Architecture: any\n"
    "Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}"
    ": ${CPACK_COMPONENT_${UPPER_COMPONENT}_DISPLAY_NAME}\n"
    "${DEB_LONG_DESCRIPTION}"
    " .\n"
    " ${CPACK_COMPONENT_${UPPER_COMPONENT}_DESCRIPTION}\n"
    )
endforeach(COMPONENT ${CPACK_COMPONENTS_ALL})

##############################################################################
# debian/copyright
set(DEBIAN_COPYRIGHT ${DEBIAN_SOURCE_DIR}/debian/copyright)
execute_process(COMMAND ${CMAKE_COMMAND} -E
  copy ${CPACK_RESOURCE_FILE_LICENSE} ${DEBIAN_COPYRIGHT}
  )

##############################################################################
# debian/rules
set(DEBIAN_RULES ${DEBIAN_SOURCE_DIR}/debian/rules)
file(WRITE ${DEBIAN_RULES}
  "#!/usr/bin/make -f\n"
  "\n"
  "BUILDDIR = build_dir\n"
  "\n"
  "build:\n"
  "	mkdir $(BUILDDIR)\n"
  "	cd $(BUILDDIR); cmake ..\n"
  "	make --no-print-directory -C $(BUILDDIR) preinstall\n"
  "	touch build\n"
  "\n"
  "binary: binary-indep binary-arch\n"
  "\n"
  "binary-indep: build\n"
  "\n"
  "binary-arch: build\n"
  "	cd $(BUILDDIR); cmake -DCOMPONENT=Unspecified -DCMAKE_INSTALL_PREFIX=../debian/tmp/usr -P cmake_install.cmake\n"
  "	cmake -E make_directory debian/tmp/DEBIAN\n"
  "	dpkg-gencontrol -p${CPACK_DEBIAN_PACKAGE_NAME}\n"
  "	dpkg --build debian/tmp ..\n"
  )

foreach(COMPONENT ${CPACK_COMPONENTS_ALL})
  set(PATH debian/tmp_${COMPONENT})
  set(PACKAGE ${CPACK_DEBIAN_PACKAGE_NAME}-${COMPONENT})
  file(APPEND ${DEBIAN_RULES}
    "	cd $(BUILDDIR); cmake -DCOMPONENT=${COMPONENT} -DCMAKE_INSTALL_PREFIX=../${PATH}/usr -P cmake_install.cmake\n"
      "	cmake -E make_directory ${PATH}/DEBIAN\n"
    "	dpkg-gencontrol -p${PACKAGE} -P${PATH}\n"
    "	dpkg --build ${PATH} ..\n"
    )
endforeach(COMPONENT ${CPACK_COMPONENTS_ALL})

file(APPEND ${DEBIAN_RULES}
  "\n"
  "clean:\n"
  "	rm -f build\n"
  "	rm -rf $(BUILDDIR)\n"
  "\n"
  ".PHONY: binary binary-arch binary-indep clean\n"
  )

execute_process(COMMAND chmod +x ${DEBIAN_RULES})

##############################################################################
# debian/compat
file(WRITE ${DEBIAN_SOURCE_DIR}/debian/compat "7")

##############################################################################
# debian/source/format
file(WRITE ${DEBIAN_SOURCE_DIR}/debian/source/format "3.0 (native)")

##############################################################################
# debian/changelog
set(DEBIAN_CHANGELOG ${DEBIAN_SOURCE_DIR}/debian/changelog)
execute_process(COMMAND date -R OUTPUT_VARIABLE DATE_TIME)
execute_process(COMMAND date +%y%m%d-6 OUTPUT_VARIABLE suffix OUTPUT_STRIP_TRAILING_WHITESPACE)
file(WRITE ${DEBIAN_CHANGELOG}
  "${CPACK_DEBIAN_PACKAGE_NAME} (0.8.15-${suffix}) natty; urgency=low\n\n"
  "  * Package built with CMake\n\n"
  " -- ${CPACK_PACKAGE_CONTACT}  ${DATE_TIME}"
  )

##############################################################################
# upload package to PPA

find_program(DPKG_BUILDPACKAGE dpkg-buildpackage)
find_program(DPUT dput)

if(NOT DPKG_BUILDPACKAGE OR NOT DPUT)
  return()
endif()

set(changes_file
  "${CPACK_DEBIAN_PACKAGE_NAME}_0.8.15-${suffix}_source.changes"
  )

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/${changes_file}
  COMMAND ${DPKG_BUILDPACKAGE} -S
  WORKING_DIRECTORY ${DEBIAN_SOURCE_DIR}
  )

add_custom_target(deploy
  ${DPUT} "ppa:purplekarrot/ppa" ${changes_file}
  DEPENDS ${CMAKE_BINARY_DIR}/${changes_file}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Debian
  )
