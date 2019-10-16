// Copyright 2019 Yunqi Ouyang
#include "cube_util/scrambler_222.hpp"

#include "cube_util/cube_222_solver.hpp"
#include "cube_util/utils.hpp"

namespace cube_util {

using cube222::kMaxLength;

Scrambler222::Scrambler222() : Scrambler222(kMaxLength) {}

Scrambler222::Scrambler222(uint16_t minScrambleLength) : Scrambler(true) {
  min_state_length_ = 4;
  min_scramble_length_ = minScrambleLength;
}
unique_ptr<MoveSequence> Scrambler222::scramble() {
  Cube222Solver s;
  do {
    s = Cube222Solver(CubieCube222::randomCube());
  } while (wca_check_ && s.isSolvableIn(min_state_length_ - 1));
  return s.generate(min_scramble_length_);
}

}  // namespace cube_util
