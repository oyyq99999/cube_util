// Copyright 2019 Yunqi Ouyang
#include "cube_util/utils.hpp"

#include <array>
#include <random>

#include <boost/algorithm/string/trim.hpp>

#include "cube_util/scramble/scrambler_222.hpp"
#include "cube_util/scramble/scrambler_333.hpp"
#include "cube_util/scramble/scrambler_nnn.hpp"

namespace cube_util {

namespace utils {

using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::to_string;
using std::array;

using boost::trim;

using constants::kNChooseMax;
using constants::kMovePerAxis;
using constants::kMovePerShift;

uint32_t choose(uint16_t n, uint16_t k) {
  static const auto cnk = [] {
    auto ret = array<array<uint32_t, kNChooseMax + 1>, kNChooseMax + 1>();
    for (auto i = 0; i <= kNChooseMax; i++) {
      ret[i][0] = ret[i][i] = 1;
      for (auto j = 1; j < i; j++) {
        ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
      }
    }
    return ret;
  }();
  return cnk[n][k];
}

bool getNParity(uint64_t index, uint16_t n) {
  uint16_t p = 0;
  for (auto i = n - 2; i >= 0; i--) {
    p ^= index % (n - i);
    index /= (n - i);
  }
  return p & 1;
}

function<int64_t()> randomizer(int64_t start, int64_t end) {
  static random_device rd;
  default_random_engine gen = default_random_engine(rd());
  uniform_int_distribution<int64_t> dist(start, end);
  return bind(dist, gen);
}

string scrambleString(int cubeSize, int length) {
  using cube222::kMaxLength;
  using cube333::kMaxPhase1Length;

  if (cubeSize == 2) {
    length = length > kMaxLength ? kMaxLength : length;
    return Scrambler222(length).scramble()->toString();
  }
  if (cubeSize == 3) {
    length = length < kMaxPhase1Length ? kMaxPhase1Length : length;
    return Scrambler333(length).scramble()->toString();
  }
  return ScramblerNNN(cubeSize).scramble()->toString();
}

string scrambleString(int cubeSize) {
  if (cubeSize == 2) {
    return scrambleString(2, cube222::kMaxLength);
  }
  if (cubeSize == 3) {
    return scrambleString(3, 21);
  }
  return scrambleString(cubeSize, (cubeSize - 2) * 20);
}

uint16_t reverseMove(uint16_t move) {
  auto amount = move % kMovePerAxis;
  move /= kMovePerAxis;
  move *= kMovePerAxis;
  return move + (kMovePerAxis - 1 - amount);
}

string move2Str(uint16_t move) {
  using constants::kFaceNames;

  auto shift = move / kMovePerShift;
  shift++;

  move %= kMovePerShift;
  int axis = move / kMovePerAxis;
  int amount = move % kMovePerAxis;
  string m;

  if (shift > 2) {
    m.append(to_string(shift));
  }
  m.append(&kFaceNames[axis], 1);
  if (shift >= 2) {
    m.append("w");
  }
  m.append(&" 2'"[amount], 1);
  trim(m);
  return m;
}

}  // namespace utils

}  // namespace cube_util
