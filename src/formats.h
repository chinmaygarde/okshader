#pragma once

#include <cstddef>

#include "logger.h"
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
  OK_UNREACHABLE;
}

constexpr size_t BytesPerPixel(PixelFormat format) {
  switch (format) {
    case PixelFormat::kA8:
      return 1u;
    case PixelFormat::kRGBA8888:
      return 4u;
  }
  OK_UNREACHABLE;
}

constexpr size_t BytesPerComponent(PixelFormat format) {
  switch (format) {
    case PixelFormat::kA8:
    case PixelFormat::kRGBA8888:
      return 1u;
  }
  OK_UNREACHABLE;
}

enum class PrimitiveType {
  kTriangle,
  kTriangleStrip,
  kTriangleFan,
};

constexpr uint32_t TrianglesForPrimitiveType(PrimitiveType type,
                                             uint32_t vertex_count) {
  switch (type) {
    case PrimitiveType::kTriangle: {
      return (vertex_count - vertex_count % 3u) / 3u;
    }
    case PrimitiveType::kTriangleStrip:
    case PrimitiveType::kTriangleFan: {
      if (vertex_count < 3u) {
        return 0u;
      } else if (vertex_count == 3u) {
        return 1u;
      } else {
        return vertex_count - 2u;
      }
    }
  }
  OK_UNREACHABLE;
}

}  // namespace ok
