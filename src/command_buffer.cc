#include "command_buffer.h"

namespace ok {

CommandBuffer::CommandBuffer() = default;

CommandBuffer::~CommandBuffer() = default;

CommandBuffer& CommandBuffer::Emplace(Command cmd) {
  commands_.emplace_back(std::move(cmd));
  return *this;
}

uint32_t CommandBuffer::GetCommandCount() const {
  return commands_.size();
}
}  // namespace ok
