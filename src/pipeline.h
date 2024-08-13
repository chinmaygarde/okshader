#pragma once

#include "Reactor.hpp"
#include "macros.h"
#include "pipeline_descriptor.h"

namespace ok {

class Pipeline {
 public:
  Pipeline(const PipelineDescriptor& desc);

  ~Pipeline();

  template <class T>
  using VertexAttributeAccessor =
      std::function<const T*(void* ptr, uint32_t index)>;

  template <class T>
  VertexAttributeAccessor<T> GetVertexAttributeAccesor(
      uint32_t location) const {
    return [entry = vertex_attribute_accessors_.at(location)->getEntry()](
               void* ptr, uint32_t index) -> const T* {
      return (const T*)((void* (*)(uint8_t*, uint32_t))entry)((uint8_t*)ptr,
                                                              index);
    };
  }

 private:
  std::map<uint32_t, std::shared_ptr<rr::Routine>> vertex_attribute_accessors_;
  OK_DISALLOW_COPY_ASSIGN_AND_MOVE(Pipeline);
};

}  // namespace ok
