// Copyright 2019 Yunqi Ouyang
#include "cube_util/puzzle/cubie_cube_nnn.hpp"

namespace cube_util {

using std::ostream;

using utils::setNPerm;
using utils::getNPerm;
using utils::setNTwist;
using utils::getNTwist;

using enums::Corners::URF;
using enums::Corners::UFL;
using enums::Corners::ULB;
using enums::Corners::UBR;
using enums::Corners::DLF;
using enums::Corners::DFR;
using enums::Corners::DRB;
using enums::Corners::DBL;

using enums::CornerTwists::kOriented;

CubieCubeNNN::CubieCubeNNN()
    : cp_ {URF, UFL, ULB, UBR, DLF, DFR, DRB, DBL}, co_ {kOriented} {}

void CubieCubeNNN::setCP(uint16_t index) {
  setNPerm(&cp_, index, kNCorner);
}

void CubieCubeNNN::setCO(uint16_t index) {
  setNTwist(&co_, index, kNCorner);
}

uint16_t CubieCubeNNN::getCPIndex() const {
  return getNPerm(cp_, kNCorner);
}

uint16_t CubieCubeNNN::getCOIndex() const {
  return getNTwist(co_, kNCorner);
}

ostream& operator<<(ostream &os, const CubieCubeNNN &cc) {
  return os << cc.toString();
}

}  // namespace cube_util
