#include "allocation.h"

#include <algorithm>
#include <cstring>

#include "logger.h"

namespace ok {

Allocation::Allocation() = default;

Allocation::~Allocation() {
  ::free(buffer_);
}

uint8_t* Allocation::GetBuffer() const {
  return buffer_;
}

Bytes Allocation::GetLength() const {
  return length_;
}

Bytes Allocation::GetReservedLength() const {
  return reserved_;
}

bool Allocation::Truncate(Bytes length, bool npot) {
  const auto reserved = npot ? ReserveNPOT(length) : Reserve(length);
  if (!reserved) {
    return false;
  }
  length_ = length;
  return true;
}

uint32_t Allocation::NextPowerOfTwoSize(uint32_t x) {
  if (x == 0) {
    return 1;
  }

  --x;

  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;

  return x + 1;
}

bool Allocation::ReserveNPOT(Bytes reserved) {
  // Reserve at least one page of data.
  reserved = std::max(Bytes{4096u}, reserved);
  return Reserve(Bytes{NextPowerOfTwoSize(reserved.GetByteSize())});
}

bool Allocation::Reserve(Bytes reserved) {
  if (reserved <= reserved_) {
    return true;
  }

  auto new_allocation = ::realloc(buffer_, reserved.GetByteSize());
  if (!new_allocation) {
    // If new length is zero, a minimum non-zero sized allocation is returned.
    // So this check will not trip and this routine will indicate success as
    // expected.
    OK_LOG << "Allocation failed. Out of host memory.";
    return false;
  }

  buffer_ = static_cast<uint8_t*>(new_allocation);
  reserved_ = reserved;

  return true;
}

}  // namespace ok
