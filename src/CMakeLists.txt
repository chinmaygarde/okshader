ok_library(ok
  allocation.cc
  allocation.h
  allocation_size.cc
  allocation_size.h
  constants.cc
  constants.h
  logger.cc
  logger.h
  macros.h
  pipeline.cc
  pipeline.h
  pipeline_descriptor.cc
  pipeline_descriptor.h
  queue.cc
  queue.h
  scalar.cc
  scalar.h
  size.cc
  size.h
  texture.cc
  texture.h
)

target_link_libraries(ok PUBLIC Reactor glm)
