#pragma once

#include <cstddef>

#include "size.h"

namespace ok {

enum class PixelFormat {
  kA8,
  kRGBA8888,
};

constexpr size_t ComponentsForFormat(PixelFormat format) {
  switch (format) {
    case PixelFormat::kA8:
      return 1u;
    case PixelFormat::kRGBA8888:
      return 4u;
  }
}

constexpr size_t BytesPerPixel(PixelFormat format) {
  switch (format) {
    case PixelFormat::kA8:
      return 1u;
    case PixelFormat::kRGBA8888:
      return 4u;
  }
}

constexpr size_t BytesPerComponent(PixelFormat format) {
  switch (format) {
    case PixelFormat::kA8:
    case PixelFormat::kRGBA8888:
      return 1u;
  }
}

}  // namespace ok
