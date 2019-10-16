// Copyright 2019 Yunqi Ouyang
#include<cube_util/Scrambler333.hpp>

#include<cube_util/Cube333Solver.hpp>
#include<cube_util/Utils.hpp>

namespace cube_util {

Scrambler333::Scrambler333() : Scrambler333(21) {}

Scrambler333::Scrambler333(uint16_t maxScrambleLength) : Scrambler(true) {
  minStateLength = 2;
  this->maxScrambleLength = maxScrambleLength;
}
unique_ptr<MoveSequence> Scrambler333::scramble() {
  Cube333Solver s;
  do {
    s = Cube333Solver(CubieCube333::randomCube());
  } while (wcaCheck && s.isSolvableIn(minStateLength - 1));
  return s.generate(maxScrambleLength);
}

}  // namespace cube_util
