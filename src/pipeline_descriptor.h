#pragma once

#include <cstddef>
#include <map>

#include "vertex_stage.h"

namespace ok {

struct VertexAttribute {
  uint32_t offset = 0u;
  uint32_t stride = 0u;
};

struct PipelineDescriptor {
  std::map<uint32_t, VertexAttribute> vertex_attributes;
  VertexStage vertex_stage;
};

}  // namespace ok
