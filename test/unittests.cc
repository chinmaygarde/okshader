#include "Reactor.hpp"
#include "command_buffer.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "gtest/gtest.h"
#include "pipeline.h"
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
  {
    rr::Return(42);  //
  }

  auto routine = Return42("Return42");

  int (*result)() = (int (*)())routine->getEntry();
  ASSERT_EQ(result(), 42);
}

TEST(OKTest, CanCreateVertexAttributeAccessor) {
  struct VertexData {
    glm::vec2 a;
    glm::vec4 b;
  };

  PipelineDescriptor desc;

  constexpr uint32_t kVertexIndex = 1u;
  constexpr uint32_t kOtherVertexIndex = 2u;

  desc.vertex_attributes[kVertexIndex].offset = offsetof(VertexData, b);
  desc.vertex_attributes[kVertexIndex].stride = sizeof(VertexData);

  desc.vertex_attributes[kOtherVertexIndex].offset = offsetof(VertexData, a);
  desc.vertex_attributes[kOtherVertexIndex].stride = sizeof(VertexData);

  auto pipeline = Pipeline{desc};

  std::vector<VertexData> data = {
      {{1, 2}, {1, 2, 3, 4}},
      {{3, 4}, {5, 6, 7, 8}},
      {{5, 6}, {9, 10, 11, 12}},
  };

  {
    auto accessor = pipeline.GetVertexAttributeAccesor<glm::vec4>(kVertexIndex);
    ASSERT_TRUE(!!accessor);
    ASSERT_EQ(*accessor(data.data(), 0), data[0].b);
    ASSERT_EQ(*accessor(data.data(), 1), data[1].b);
    ASSERT_EQ(*accessor(data.data(), 2), data[2].b);
  }
  {
    auto accessor =
        pipeline.GetVertexAttributeAccesor<glm::vec2>(kOtherVertexIndex);
    ASSERT_TRUE(!!accessor);
    ASSERT_EQ(*accessor(data.data(), 0), data[0].a);
    ASSERT_EQ(*accessor(data.data(), 1), data[1].a);
    ASSERT_EQ(*accessor(data.data(), 2), data[2].a);
  }
}

TEST(OKTest, CanCreateCommandBuffer) {
  PipelineDescriptor desc;

  auto pipeline = Pipeline{desc};

  CommandBuffer cmd_buffer;
  cmd_buffer.Emplace(Command{
      .pipeline = &pipeline,
      .vertex_count = 300,
  });
  cmd_buffer.Emplace(Command{
      .pipeline = &pipeline,
      .vertex_count = 400,
  });
  cmd_buffer.Emplace(Command{
      .pipeline = &pipeline,
      .vertex_count = 500,
  });
  cmd_buffer.Emplace(Command{
      .pipeline = &pipeline,
      .vertex_count = 600,
  });
  ASSERT_EQ(cmd_buffer.GetCommandCount(), 4u);
}

TEST(OKTest, CanConstructTriangleListFromCommand) {
  PipelineDescriptor desc;
  auto pipeline = Pipeline{desc};

  Command command;
  command.pipeline = &pipeline;
  command.vertex_count = 3u;
  command.primitive_type = PrimitiveType::kTriangle;
}

}  // namespace ok::testing
