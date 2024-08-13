#pragma once

#include "pipeline.h"

namespace ok {

struct Command {
  const Pipeline* pipeline = nullptr;
  uint32_t vertex_count = 0u;
};

}  // namespace ok
