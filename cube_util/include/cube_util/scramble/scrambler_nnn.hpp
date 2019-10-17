// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_NNN_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_NNN_HPP_
#include "cube_util/scramble/scrambler.hpp"

#include <memory>

namespace cube_util {

///////////////////////////////////////////////////////////////////////////////
/// An NxNxN cube scrambler which is able to give WCA-compatible scrambles.
///////////////////////////////////////////////////////////////////////////////
class ScramblerNNN : public Scrambler {
 public:
  /**
   * Constructor of the class.
   * @param cube_size size of the cube to scramble
   */
  explicit ScramblerNNN(uint16_t cube_size);
  unique_ptr<MoveSequence> scramble() override;
 private:
  /** Size of the cube to apply the scrambler to. */
  uint16_t cube_size_;
  /** Length of the scramble to generate. */
  uint16_t scramble_length_;
};

}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_SCRAMBLER_NNN_HPP_
