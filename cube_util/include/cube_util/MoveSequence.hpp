// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_MOVESEQUENCE_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_MOVESEQUENCE_HPP_
#include<iostream>
#include<string>
#include<vector>

namespace cube_util {

using std::ostream;
using std::string;
using std::vector;

////////////////////////////////////////////////////////////////////////////////
/// A class representing a move sequence object, which contains move sequence
/// in numbers and length, and can be converted to string.
////////////////////////////////////////////////////////////////////////////////
class MoveSequence {
  /**
   * Outputs the sequence
   */
  friend ostream& operator<<(ostream& os, const MoveSequence &s);

 protected:
  /** Move sequence in numbers */
  vector<uint16_t> sequence;

  /** Move Sequence length */
  uint16_t length;

  /**
   * Constructor of the class.
   * @param moves move sequence in numbers
   */
  explicit MoveSequence(const vector<uint16_t> &moves);

 public:
  /**
   * Get move sequence in numbers.
   * @returns move sequence in numbers
   */
  vector<uint16_t> getMoves() const;

  /**
   * Get move sequence length.
   * @returns sequence length
   */
  uint16_t getLength() const;

  /**
   * Get the move sequence in humban-readable format.
   * @returns the sequence string
   */
  virtual string toString() const = 0;

  virtual ~MoveSequence() = default;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_MOVESEQUENCE_HPP_
