# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

find_package(Boost NO_MODULE)
include("${Boost_USE_FILE}")

include_directories(${CMAKE_BINARY_DIR}/include)

add_custom_target(examples)

foreach(name Empty SphereMapping Triangle)
  add_executable(${name} EXCLUDE_FROM_ALL ${name})
  add_dependencies(examples ${name})
  target_link_libraries(${name} Maoni MaoniMain)

  if(NOT MAONI_SKIP_ICET)
    add_executable(${name}_IceT EXCLUDE_FROM_ALL ${name}.cpp)
    add_dependencies(examples ${name}_IceT)
    target_link_libraries(${name}_IceT MaoniIceT MaoniMain)
  endif(NOT MAONI_SKIP_ICET)
endforeach(name)
