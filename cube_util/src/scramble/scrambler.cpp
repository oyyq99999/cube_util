// Copyright 2019 Yunqi Ouyang
#include "cube_util/scramble/scrambler.hpp"

#include "cube_util/scramble/scrambler_222.hpp"
#include "cube_util/scramble/scrambler_333.hpp"
#include "cube_util/scramble/scrambler_nnn.hpp"

namespace cube_util {

using std::make_unique;

Scrambler::Scrambler(bool wca_check) {
  wca_check_ = wca_check;
}

unique_ptr<Scrambler> Scrambler::instance(uint16_t size) {
  switch (size) {
    case 2:
      return make_unique<Scrambler222>();
    case 3:
      return make_unique<Scrambler333>();
    default:
      return make_unique<ScramblerNNN>(size);
  }
}

}  // namespace cube_util
