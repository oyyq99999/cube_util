// Copyright 2019 Yunqi Ouyang
#include "cube_util/scrambler_333.hpp"

#include "cube_util/cube_333_solver.hpp"
#include "cube_util/utils.hpp"

namespace cube_util {

Scrambler333::Scrambler333() : Scrambler333(21) {}

Scrambler333::Scrambler333(uint16_t maxScrambleLength) : Scrambler(true) {
  min_scramble_length_ = 2;
  max_scramble_length_ = maxScrambleLength;
}
unique_ptr<MoveSequence> Scrambler333::scramble() {
  Cube333Solver s;
  do {
    s = Cube333Solver(CubieCube333::randomCube());
  } while (wca_check_ && s.isSolvableIn(min_scramble_length_ - 1));
  return s.generate(max_scramble_length_);
}

}  // namespace cube_util
