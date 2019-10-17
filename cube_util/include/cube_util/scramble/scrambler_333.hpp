// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_333_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_333_HPP_
#include <memory>

#include "cube_util/scramble/scrambler.hpp"

namespace cube_util {

///////////////////////////////////////////////////////////////////////////////
/// A 3x3x3 cube scrambler which is able to give WCA-compatible scrambles.
///////////////////////////////////////////////////////////////////////////////
class Scrambler333 : public Scrambler {
 public:
  /**
   * The default constructor.
   */
  Scrambler333();

  /**
   * Constructor of the class.
   * @param maxScrambleLength upper limit of the scramble sequence
   * length
   */
  explicit Scrambler333(uint16_t maxScrambleLength);

  unique_ptr<MoveSequence> scramble() override;
 private:
  /// Upper limit of the scramble sequence length, which is useful
  /// for bigger cubes
  uint16_t max_scramble_length_ = 21;
};

}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_333_HPP_
