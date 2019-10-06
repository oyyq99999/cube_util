// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLER_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLER_HPP_
#include<cstdint>

#include<memory>

#include<cube_util/MoveSequence.hpp>

namespace cube_util {

using std::unique_ptr;

////////////////////////////////////////////////////////////////////////////////
/// A general cube scrambler interface which is able to give
/// WCA-compatible scrambles.
////////////////////////////////////////////////////////////////////////////////
class Scrambler {
 protected:
  /** Whether to check the scramble state to satisfy WCA regulations */
  bool wcaCheck = true;

  /** WCA scramble state requirement */
  uint16_t minStateLength = 2;

  /// Lower limit of the scramble sequence length, which is useful
  /// for small cubes
  uint16_t minScrambleLength = 0;

 public:
  /**
   * Constructor of the class.
   * @param wcaCheck whether check for WCA state requirements
   */
  explicit Scrambler(bool wcaCheck);

  /**
   * The scramble function. This generates a new scramble on each call.
   * @returns the scramble sequence
   */
  virtual unique_ptr<MoveSequence> scramble() = 0;

  virtual ~Scrambler() = default;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLER_HPP_
