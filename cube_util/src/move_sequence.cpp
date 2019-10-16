// Copyright 2019 Yunqi Ouyang
#include "cube_util/move_sequence.hpp"

namespace cube_util {

MoveSequence::MoveSequence(const vector<uint16_t> &moves): sequence_(moves) {
  length_ = sequence_.size();
}

vector<uint16_t> MoveSequence::getMoves() const {
  return sequence_;
}

uint16_t MoveSequence::getLength() const {
  return length_;
}

ostream& operator<<(ostream& os, const MoveSequence &s) {
  return os << s.toString();
}

}  // namespace cube_util
