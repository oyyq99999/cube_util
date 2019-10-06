// Copyright 2019 Yunqi Ouyang
#include<cube_util/MoveSequence.hpp>

namespace cube_util {

MoveSequence::MoveSequence(const vector<uint16_t> &moves): sequence(moves) {
  length = sequence.size();
}

vector<uint16_t> MoveSequence::getMoves() const {
  return this->sequence;
}

uint16_t MoveSequence::getLength() const {
  return this->length;
}

ostream& operator<<(ostream& os, const MoveSequence &s) {
  return os << s.toString();
}

}  // namespace cube_util
