#pragma once

#include <array>
#include <cstddef>

#include "allocation.h"
#include "formats.h"

namespace ok {

template <PixelFormat PixelFormat_>
class Texture final {
 public:
  Texture() = default;

  Texture(ISize size) : size_(size) {}

  constexpr PixelFormat GetPixelFormat() const { return PixelFormat_; }

  [[nodiscard]]
  bool AllocateMemory() {
    for (size_t i = 0; i < channels_.size(); i++) {
      if (!channels_[i].Truncate(
              Bytes{BytesPerComponent(PixelFormat_) * size_.Area()}, false)) {
        return false;
      }
    }
    return true;
  }

  Bytes GetReservedSize() const {
    Bytes size;
    for (size_t i = 0; i < channels_.size(); i++) {
      size += channels_[i].GetReservedLength();
    }
    return size;
  }

 private:
  const ISize size_;
  std::array<Allocation, ComponentsForFormat(PixelFormat_)> channels_;
};

}  // namespace ok
