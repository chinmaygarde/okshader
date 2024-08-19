#include "input_assembler.h"

namespace ok {

InputAssembler::InputAssembler() = default;

InputAssembler::~InputAssembler() = default;

struct TriangleVertexIndex {
  uint32_t triangle_index = 0u;
  uint32_t vertex_index = 0u;
};

bool InputAssembler::ProcessCommand(const Command& cmd) {
  const auto triangle_count =
      TrianglesForPrimitiveType(cmd.primitive_type, cmd.vertex_count);
  if (triangle_count == 0u) {
    return true;
  }
  const auto triangles_start_index = triangles_.size();
  triangles_.resize(triangles_.size() + triangle_count);
  auto vertex_stage = cmd.pipeline->GetVertexStage();
  PerVertex data;
  switch (cmd.primitive_type) {
    case PrimitiveType::kTriangle: {
      for (size_t i = 0; i < cmd.vertex_count; i++) {
        data.vertex_id = i;
        vertex_stage(&data);
        triangles_[triangles_start_index + (i / 3u)].verts[i % 3u] =
            data.position;
      }
    } break;
    case PrimitiveType::kTriangleStrip: {
      OK_UNIMPLEMENTED;
    } break;
    case PrimitiveType::kTriangleFan: {
      OK_UNIMPLEMENTED;
    } break;
  }
  return true;
}

}  // namespace ok
