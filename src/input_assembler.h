#pragma once

#include <vector>

#include "command.h"
#include "glm/glm.hpp"
#include "macros.h"

namespace ok {

class InputAssembler {
 public:
  struct Triangle {
    union {
      struct {
        glm::vec3 a;
        glm::vec3 b;
        glm::vec3 c;
      };
      glm::vec3 verts[3];
    };
  };

  InputAssembler();

  ~InputAssembler();

  bool ProcessCommand(const Command& cmd);

 private:
  std::vector<Triangle> triangles_;

  OK_DISALLOW_COPY_ASSIGN_AND_MOVE(InputAssembler);
};

}  // namespace ok
