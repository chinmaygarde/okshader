#pragma once

#include "glm/glm.hpp"

namespace ok {

// Similar to gl_PerVertex
struct PerVertex {
  // Similar to gl_Position
  glm::vec4 position;
  // Similar to gl_VertexID
  uint32_t vertex_id;
};

using VertexStage = void (*)(const PerVertex* data);

}  // namespace ok
