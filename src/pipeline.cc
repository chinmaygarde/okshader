#include "pipeline.h"

#include "Reactor.hpp"

namespace ok {

using namespace rr;

auto CreateVertexAttributeAccessor(const VertexAttribute& desc) {
  Function<Pointer<Byte>(Pointer<Byte>, UInt)> vertex_attribute_accessor;
  {
    Pointer<Byte> data_ptr = vertex_attribute_accessor.Arg<0u>();
    UInt index = vertex_attribute_accessor.Arg<1u>();
    Return(data_ptr + (index * desc.stride) + desc.offset);
  }
  return vertex_attribute_accessor("vertex_attribute_accessor");
}

Pipeline::Pipeline(const PipelineDescriptor& desc)
    : vertex_stage_(desc.vertex_stage) {
  for (const auto& vertex_attribute : desc.vertex_attributes) {
    vertex_attribute_accessors_[vertex_attribute.first] =
        CreateVertexAttributeAccessor(vertex_attribute.second);
  }
}

Pipeline::~Pipeline() = default;

VertexStage Pipeline::GetVertexStage() const {
  return vertex_stage_;
}

}  // namespace ok
