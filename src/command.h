#pragma once

#include "formats.h"
#include "pipeline.h"

namespace ok {

struct Command {
  const Pipeline* pipeline = nullptr;
  uint32_t vertex_count = 0u;
  PrimitiveType primitive_type = PrimitiveType::kTriangle;
};

}  // namespace ok
