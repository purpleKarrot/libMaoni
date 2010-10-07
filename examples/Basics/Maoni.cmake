
maoni_module(Enum
  SOURCE Enum.cpp
  )

maoni_module(Triangle
  SOURCE Triangle.cpp
  )

MAONI_MODULE(SphereMapping
  SOURCE SphereMapping.cpp
  DATA
    data/sphere0.jpg
    data/sphere1.jpg
    data/sphere2.jpg
    data/sphere3.jpg
  )
