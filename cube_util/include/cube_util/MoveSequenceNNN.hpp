// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_MOVESEQUENCENNN_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_MOVESEQUENCENNN_HPP_
#include<string>
#include<vector>

#include<cube_util/MoveSequence.hpp>

namespace cube_util {

////////////////////////////////////////////////////////////////////////////////
/// A class representing a move sequence object for an NxNxN cube.
////////////////////////////////////////////////////////////////////////////////
class MoveSequenceNNN : public MoveSequence {
  /** The cube size */
  uint16_t size;

 public:
  /**
   * Constructor of the class.
   * @param size size of the cube
   * @param s the sequence string to parse from
   */
  MoveSequenceNNN(uint16_t size, const string &s);

  /**
   * Constructor of the class.
   * @param size size of the cube
   * @param moves the sequence in numbers
   */
  MoveSequenceNNN(uint16_t size, vector<uint16_t> moves);

  string toString() const override;

  /**
   * Parse a move sequence string to number format.
   * @param s the sequence string to parse from
   * @returns the parsed move sequence
   */
  static vector<uint16_t> parse(const string &s);
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_MOVESEQUENCENNN_HPP_
