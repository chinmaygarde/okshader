#pragma once

#include "allocation_size.h"
#include "macros.h"

namespace ok {

class Allocation {
 public:
  //----------------------------------------------------------------------------
  /// @brief      Constructs a new zero-sized allocation.
  ///
  Allocation();

  //----------------------------------------------------------------------------
  /// @brief      Destroys the allocation.
  ///
  ~Allocation();

  //----------------------------------------------------------------------------
  /// @brief      Gets the pointer to the start of the allocation.
  ///
  ///             This pointer is only valid till the next call to `Truncate`.
  ///
  /// @return     The pointer to the start of the allocation.
  ///
  uint8_t* GetBuffer() const;

  //----------------------------------------------------------------------------
  /// @brief      Gets the length of the allocation.
  ///
  /// @return     The length.
  ///
  Bytes GetLength() const;

  //----------------------------------------------------------------------------
  /// @brief      Gets the reserved length of the allocation. Calls to truncate
  ///             may be ignored till the length exceeds the reserved length.
  ///
  /// @return     The reserved length.
  ///
  Bytes GetReservedLength() const;

  //----------------------------------------------------------------------------
  /// @brief      Resize the underlying allocation to at least given number of
  ///             bytes.
  ///
  ///             In case of failure, false is returned and the underlying
  ///             allocation remains unchanged.
  ///
  /// @warning    Pointers to buffers obtained via previous calls to `GetBuffer`
  ///             may become invalid at this point.
  ///
  /// @param[in]  length  The length.
  /// @param[in]  npot    Whether to round up the length to the next power of
  ///                     two.
  ///
  /// @return     If the underlying allocation was resized to the new size.
  ///
  [[nodiscard]] bool Truncate(Bytes length, bool npot = true);

  //----------------------------------------------------------------------------
  /// @brief      Gets the next power of two size.
  ///
  /// @param[in]  x     The size.
  ///
  /// @return     The next power of two of x.
  ///
  static uint32_t NextPowerOfTwoSize(uint32_t x);

 private:
  uint8_t* buffer_ = nullptr;
  Bytes length_;
  Bytes reserved_;

  [[nodiscard]] bool Reserve(Bytes reserved);

  [[nodiscard]] bool ReserveNPOT(Bytes reserved);

  OK_DISALLOW_COPY_AND_ASSIGN(Allocation);
};

}  // namespace ok
