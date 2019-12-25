// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_HPP_
#include <cstdint>

#include <memory>

#include "cube_util/move_sequence.hpp"

namespace cube_util {

using std::unique_ptr;

////////////////////////////////////////////////////////////////////////////////
/// A general cube scrambler interface which is able to give
/// WCA-compatible scrambles.
////////////////////////////////////////////////////////////////////////////////
class Scrambler {
 public:
  /**
   * Constructor of the class.
   * @param wca_check whether check for WCA state requirements
   */
  explicit Scrambler(bool wca_check);

  /**
   * The scramble function. This generates a new scramble on each call.
   * @returns the scramble sequence
   */
  virtual unique_ptr<MoveSequence> scramble() = 0;

  virtual ~Scrambler() = default;

  static unique_ptr<Scrambler> instance(uint16_t size);

 protected:
  /** Whether to check the scramble state to satisfy WCA regulations */
  bool wca_check_ = true;

  /** WCA scramble state requirement */
  uint16_t min_state_length_ = 2;

  /// Lower limit of the scramble sequence length, which is useful
  /// for small cubes
  uint16_t min_scramble_length_ = 0;
};

}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_HPP_
