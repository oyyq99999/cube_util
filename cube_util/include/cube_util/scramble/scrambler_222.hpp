// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_222_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_222_HPP_
#include <memory>

#include "cube_util/scramble/scrambler.hpp"

namespace cube_util {

///////////////////////////////////////////////////////////////////////////////
/// A 2x2x2 cube scrambler which is able to give WCA-compatible scrambles.
///////////////////////////////////////////////////////////////////////////////
class Scrambler222 : public Scrambler {
 public:
  /**
   * The default constructor.
   */
  Scrambler222();

  /**
   * Constructor of the class.
   * @param minScrambleLength lower limit of the scramble sequence length
   */
  explicit Scrambler222(uint16_t minScrambleLength);

  unique_ptr<MoveSequence> scramble() override;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_222_HPP_
