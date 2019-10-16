// Copyright 2019 Yunqi Ouyang
#include "cube_util/puzzle/cubie_cube_222.hpp"

#include <sstream>

namespace cube_util {

using std::invalid_argument;
using std::ostringstream;
using std::endl;

using constants::kNFace;
using constants::kMovePerAxis;

using enums::Colors::U;
using enums::Colors::D;

using enums::Moves::Ux1;
using enums::Moves::Rx1;
using enums::Moves::Fx1;

using enums::Corners::URF;
using enums::Corners::UFL;
using enums::Corners::ULB;
using enums::Corners::UBR;
using enums::Corners::DLF;
using enums::Corners::DFR;
using enums::Corners::DRB;
using enums::Corners::DBL;

using enums::CornerTwists::kOriented;
using enums::CornerTwists::kClockwise;
using enums::CornerTwists::kCounterClockwise;

using cube222::kFaceletPerFace;
using cube222::kFaceletMap;

using utils::setNPerm;
using utils::getNPerm;
using utils::setNTwist;
using utils::getNTwist;
using utils::randomizer;

CubieCube222::CubieCube222(const array<uint16_t, kNCorner> &perm,
                           const array<uint16_t, kNCorner> &twist) {
  int twistsTotal = 0;
  uint16_t mask = 0;

  for (auto i = 0; i < kNCorner; i++) {
    // (a & 0xfff8) != 0 is equivalent to a > 7 for uint16_t
    if ((perm[i] & 0xfff8) != 0 || (mask & (1 << perm[i])) != 0) {
      throw invalid_argument("invalid permutation!");
    }
    mask |= 1 << perm[i];
    if (twist[i] < kOriented || twist[i] > kCounterClockwise) {
      throw invalid_argument("invalid orientation!");
    }
    twistsTotal += twist[i];

    // assume all things are good, if we find something is wrong later,
    // we throw an exception
    cp_[i] = perm[i];
    co_[i] = twist[i];
  }

  if (twistsTotal % 3 != 0) {
    throw invalid_argument("wrong orientation!");
  }
}

CubieCube222::CubieCube222(uint16_t perm, uint16_t twist) {
  if (perm >= kNPerm || twist >= kNTwist) {
    throw invalid_argument("invalid parameters!");
  }
  setCP(perm);
  setCO(twist);
}

CubieCube222::CubieCube222(uint32_t index)
    : CubieCube222(index / kNTwist, index % kNTwist) {}

void CubieCube222::setCP(uint16_t index) {
  setNPerm(&cp_, index, kNCorner - 1);
}

void CubieCube222::setCO(uint16_t index) {
  setNTwist(&co_, index, kNCorner - 1);
}

uint16_t CubieCube222::getCPIndex() const {
  return getNPerm(cp_, kNCorner - 1);
}

uint16_t CubieCube222::getCOIndex() const {
  return getNTwist(co_, kNCorner - 1);
}

void CubieCube222::move(uint16_t move) {
  move %= kNMove;
  cubeMult(*this, getMoveCube(move), this);
}

void CubieCube222::cubeMult(const CubieCube222 &one,
                            const CubieCube222 &another,
                            CubieCube222 *result) {
  auto perm = array<uint16_t, kNCorner>();
  auto twist = array<uint16_t, kNCorner>();
  for (auto i = 0; i < kNCorner; i++) {
    perm[i] = one.cp_[another.cp_[i]];
    twist[i] = (one.co_[another.cp_[i]] + another.co_[i]) % 3;
  }
  result->cp_ = perm;
  result->co_ = twist;
}

string CubieCube222::toString() const {
  ostringstream os;
  os << "Perms:";
  for (auto i = 0; i < kNCorner; i++) {
    os << " " << cp_[i];
  }
  os << endl << "Twists:";
  for (auto i = 0; i < kNCorner; i++) {
    os << " " << co_[i];
  }
  os << endl;
  return os.str();
}

FaceletCubeNNN CubieCube222::toFaceletCube() const {
  auto f = vector<uint16_t>(kNFace * kFaceletPerFace);
  for (auto i = 0; i < kNCorner; i++) {
    auto piece = cp_[i];
    auto orient = co_[i];
    for (auto j = 0; j < 3; j++) {
      f[kFaceletMap[i][(j + orient) % 3]] =
          kFaceletMap[piece][j] / kFaceletPerFace;
    }
  }
  return FaceletCubeNNN(2, f);
}

CubieCube222 CubieCube222::fromFaceletCube(const FaceletCubeNNN &fc) {
  if (fc.getSize() != 2) {
    throw invalid_argument("needs a 2x2x2 cube!");
  }
  auto f = fc.getFacelets();
  array<uint16_t, kNCorner> perm;
  array<uint16_t, kNCorner> twist;
  uint16_t color1, color2, ori;
  for (auto i = 0; i < kNCorner; i++) {
    for (ori = 0; ori < 3; ori++) {
      if (f[kFaceletMap[i][ori]] == U || f[kFaceletMap[i][ori]] == D) {
        break;
      }
    }
    color1 = f[kFaceletMap[i][(ori + 1) % 3]];
    color2 = f[kFaceletMap[i][(ori + 2) % 3]];
    for (auto j = 0; j < kNCorner; j++) {
      if (color1 == kFaceletMap[j][1] / kFaceletPerFace &&
          color2 == kFaceletMap[j][2] / kFaceletPerFace) {
        perm[i] = j;
        twist[i] = ori;
        break;
      }
    }
  }
  return CubieCube222(perm, twist);
}

CubieCube222 CubieCube222::randomCube() {
  auto r = randomizer(0, kNTwist * kNPerm - 1);
  return CubieCube222(r());
}

CubieCube222 CubieCube222::getMoveCube(uint16_t move) {
  static auto moveCubeTable = [] {
    auto ret = array<CubieCube222, kNMove>();
    ret[Ux1] = CubieCube222({UBR, URF, UFL, ULB, DLF, DFR, DRB, DBL},
                            {kOriented});
    ret[Rx1] = CubieCube222(
        {DFR, UFL, ULB, URF, DLF, DRB, UBR, DBL},
        {kCounterClockwise, kOriented, kOriented, kClockwise,
            kOriented, kClockwise, kCounterClockwise, kOriented});
    ret[Fx1] = CubieCube222(
        {UFL, DLF, ULB, UBR, DFR, URF, DRB, DBL},
        {kClockwise, kCounterClockwise, kOriented, kOriented,
            kClockwise, kCounterClockwise, kOriented, kOriented});

    for (auto i = 0; i < kNMove; i += kMovePerAxis) {
      for (auto j = 1; j < kMovePerAxis; j++) {
        ret[i + j] = CubieCube222();
        cubeMult(ret[i + j - 1], ret[i], &ret[i + j]);
      }
    }
    return ret;
  }();
  return moveCubeTable[move];
}

uint16_t CubieCube222::getPermMove(uint16_t perm, uint16_t move) {
  static auto moveTable = [] {
    auto ret = array<array<uint16_t, kNMove>, kNPerm>();
    CubieCube222 c = CubieCube222();
    CubieCube222 d = CubieCube222();
    for (auto i = 0; i < kNPerm; i++) {
      c.setCP(i);
      for (auto j = 0; j < kNMove; j++) {
        cubeMult(c, getMoveCube(j), &d);
        ret[i][j] = d.getCPIndex();
      }
    }
    return ret;
  }();
  return moveTable[perm][move];
}

uint16_t CubieCube222::getTwistMove(uint16_t twist, uint16_t move) {
  static auto moveTable = [] {
    auto ret = array<array<uint16_t, kNMove>, kNTwist>();
    CubieCube222 c = CubieCube222();
    CubieCube222 d = CubieCube222();
    for (auto i = 0; i < kNTwist; i++) {
      c.setCO(i);
      for (auto j = 0; j < kNMove; j++) {
        cubeMult(c, getMoveCube(j), &d);
        ret[i][j] = d.getCOIndex();
      }
    }
    return ret;
  }();
  return moveTable[twist][move];
}

bool CubieCube222::operator==(const CubieCube222 &that) const {
  return getCPIndex() == that.getCPIndex() && getCOIndex() == that.getCOIndex();
}

}  // namespace cube_util
