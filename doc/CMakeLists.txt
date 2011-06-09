##
# Copyright (c) 2009 Daniel Pfeifer, University of Zurich
##

find_package(Boost REQUIRED COMPONENTS boostbook quickbook NO_MODULE)
include("${Boost_USE_FILE}")

include(BoostAddReference)
include(AddDocumentation)

boost_add_reference(maoni-ref
  ../include/Maoni/Color.hpp
  ../include/Maoni/Enum.hpp
  ../include/Maoni/RenderAlgorithm.hpp
  ../include/Maoni/ScopedLocks.hpp
  ../include/Maoni/ShaderProgram.hpp
  ../include/Maoni/Texture.hpp
  ../include/Maoni/Vector.hpp
  XSLTPROC_PARAMETERS
    boost.doxygen.header.prefix=Maoni
  )

add_documentation(libMaoni.qbk
    motivation.qbk
    getstarted.qbk
    tutorial.qbk
    examples.qbk
    maoni-ref.xml
    design.qbk
    software.qbk
  IMAGES
    images/Splashscreen.jpg
    images/parallel_dragon.jpg
    images/dragon_blinnphong.jpg
    images/dragon_comicstyle.jpg
    images/rockerarm_fixedfunction.jpg
    images/dragon_spheremapping.jpg
    images/dgl_bump_mapping.jpg
    images/ozone_bump_mapping.jpg
    images/swiftless_bump_mapping.jpg
    images/dragon_brick.jpg
  )
