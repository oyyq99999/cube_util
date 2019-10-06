// Copyright 2019 Yunqi Ouyang
#include<cube_util/MoveSequenceNNN.hpp>

#include<boost/algorithm/string/join.hpp>
#include<boost/algorithm/string/regex.hpp>
#include<boost/regex.hpp>

#include<cube_util/Utils.hpp>

using boost::algorithm::join;
using boost::smatch;
using boost::regex;

namespace cube_util {

using constants::FACE_NAMES;
using constants::N_MOVE_PER_SHIFT;
using constants::N_MOVE_PER_AXIS;

using utils::move2Str;

MoveSequenceNNN::MoveSequenceNNN(uint16_t size, const string &s)
    : MoveSequence(MoveSequenceNNN::parse(s)) {
  this->size = size;
}

MoveSequenceNNN::MoveSequenceNNN(uint16_t size, vector<uint16_t> moves)
    : MoveSequence(moves) {
  this->size = size;
}

vector<uint16_t> MoveSequenceNNN::parse(const string &s) {
  auto delimeter = regex("\\s+");
  vector<string> moveStrs;
  split_regex(moveStrs, s, delimeter);

  vector<uint16_t> moves;

  // Groups: 1 for single layer turn axis name,
  //         2 for shifts,
  //         3 for wide turn axis name,
  //         4 for amount
  auto pattern = regex("^(?:([URFDLB])|([2-9]|[1-9]\\d+)?([URFDLB])w)([2'])?$");
  smatch m;
  for (auto str : moveStrs) {
    auto shift = 1;
    auto amount = 0;
    if (regex_match(str, m, pattern)) {
      auto axis = string(FACE_NAMES).find(m[3] == "" ? m[1] : m[3]);

      shift = (m[3] == "" ? 1 : 2);
      shift = (m[2] == "" ? shift : stoi(m[2]));
      shift--;

      amount = (m[4] == "" ? 0 : string(" 2'").find(m[4]));

      uint16_t move = shift * N_MOVE_PER_SHIFT +
                      axis * N_MOVE_PER_AXIS +
                      amount;
      moves.push_back(move);
    }
  }
  return moves;
}

string MoveSequenceNNN::toString() const {
  vector<string> strVec;
  for (auto m : sequence) {
    strVec.push_back(move2Str(m));
  }
  return join(strVec, " ");
}

}  // namespace cube_util
