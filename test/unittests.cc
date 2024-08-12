#include "Reactor.hpp"
#include "gtest/gtest.h"
#include "texture.h"

namespace ok::testing {

TEST(OKTest, CanCreateTexture) {
  {
    Texture<PixelFormat::kRGBA8888> texture;
    ASSERT_EQ(texture.GetPixelFormat(), PixelFormat::kRGBA8888);
  }
  {
    Texture<PixelFormat::kRGBA8888> texture({800, 600});
    ASSERT_EQ(texture.GetPixelFormat(), PixelFormat::kRGBA8888);
    ASSERT_EQ(texture.GetReservedSize(), Bytes{0u});
    ASSERT_TRUE(texture.AllocateMemory());
    ASSERT_EQ(texture.GetReservedSize(), Bytes{800 * 600 * 4});
  }
  {
    Texture<PixelFormat::kA8> texture({800, 600});
    ASSERT_EQ(texture.GetPixelFormat(), PixelFormat::kA8);
    ASSERT_EQ(texture.GetReservedSize(), Bytes{0u});
    ASSERT_TRUE(texture.AllocateMemory());
    ASSERT_EQ(texture.GetReservedSize(), Bytes{800 * 600 * 1});
  }
}

TEST(OKTest, CanCreateReactor) {
  rr::Function<rr::Int(rr::Void)> Return42;
  { rr::Return(42); }

  auto routine = Return42("Return42");

  int (*result)() = (int (*)())routine->getEntry();
  ASSERT_EQ(result(), 42);
}

}  // namespace ok::testing
