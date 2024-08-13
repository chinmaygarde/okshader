#pragma once

#include "command.h"
#include "macros.h"

namespace ok {

class CommandBuffer {
 public:
  CommandBuffer();

  ~CommandBuffer();

  CommandBuffer& Emplace(Command cmd);

  uint32_t GetCommandCount() const;

 private:
  std::vector<Command> commands_;

  OK_DISALLOW_COPY_ASSIGN_AND_MOVE(CommandBuffer);
};

}  // namespace ok
