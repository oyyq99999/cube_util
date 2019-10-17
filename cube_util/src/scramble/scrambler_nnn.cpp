// Copyright 2019 Yunqi Ouyang
#include "cube_util/scramble/scrambler_nnn.hpp"

#include "cube_util/move_sequence_nnn.hpp"
#include "cube_util/puzzle/facelet_cube_nnn.hpp"
#include "cube_util/utils.hpp"

namespace cube_util {

using std::invalid_argument;
using std::make_unique;
using std::to_string;

using constants::kMaxRandomStateCubeSize;
using constants::kMaxSize;
using constants::kMovePerAxis;
using constants::kMovePerShift;
using constants::kNAxis;

using utils::randomizer;

ScramblerNNN::ScramblerNNN(uint16_t cube_size) : Scrambler(true) {
  if (cube_size <= kMaxRandomStateCubeSize) {
    throw invalid_argument("Cube smaller than " +
                           to_string(kMaxRandomStateCubeSize) +
                           " should use random state scrambler.");
  }
  if (cube_size > kMaxSize) {
    throw invalid_argument("The cube is too big");
  }
  cube_size_ = cube_size;
  scramble_length_ = (cube_size_ - 2) * 20;
}

unique_ptr<MoveSequence> ScramblerNNN::scramble() {
  vector<uint16_t> seq;
  auto fc = FaceletCubeNNN(cube_size_);
  do {
    seq.clear();
    fc.reset();
    uint16_t count = 0;
    int16_t last_axis = -1;
    auto turned = vector<bool>(cube_size_ - 1, false);
    auto r = randomizer(0, 3 * kMovePerAxis * (cube_size_ - 1) - 1);
    while (count < scramble_length_) {
      auto move = r();
      auto axis = (move / kMovePerAxis) % kNAxis;
      auto shift = move / kMovePerShift;

      // mapping DLB axes to URF axes, counting from face layer inwards
      if (axis >= kNAxis >> 1) {
        axis -= kNAxis >> 1;
        shift += cube_size_ >> 1;
      }

      if (axis != last_axis) {
        fill(turned.begin(), turned.end(), false);
      } else if (turned[shift] == true) {
        continue;
      }

      turned[shift] = true;
      last_axis = axis;
      seq.push_back(move);
      fc.move(move);
      count++;
    }
  } while (wca_check_ && fc.isSolvableIn(min_state_length_ - 1));
  return make_unique<MoveSequenceNNN>(cube_size_, seq);
}

}  // namespace cube_util
