#pragma once

#include <cstddef>
#include <map>

namespace ok {

enum class VectorSize {
  kOne = 1u,
  kTwo,
  kThree,
  kFour,
};

enum class Type {
  kUnsignedByte,
  kByte,
  kUnsignedShort,
  kShort,
  kFloat,
};

struct VertexAttribute {
  uint32_t offset = 0u;
  uint32_t stride = 0u;
};

struct PipelineDescriptor {
  std::map<uint32_t, VertexAttribute> vertex_attributes;
};

}  // namespace ok
