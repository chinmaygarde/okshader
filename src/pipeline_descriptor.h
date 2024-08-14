#pragma once

#include <cstddef>
#include <map>

namespace ok {

struct VertexAttribute {
  uint32_t offset = 0u;
  uint32_t stride = 0u;
};

struct PipelineDescriptor {
  std::map<uint32_t, VertexAttribute> vertex_attributes;
};

}  // namespace ok
