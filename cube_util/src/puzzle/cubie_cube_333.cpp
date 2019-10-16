// Copyright 2019 Yunqi Ouyang
#include "cube_util/puzzle/cubie_cube_333.hpp"

#include <sstream>

namespace cube_util {

using std::invalid_argument;
using std::ostringstream;
using std::endl;

using constants::kNFace;
using constants::kMovePerAxis;

using enums::Moves::Ux1;
using enums::Moves::Rx1;
using enums::Moves::Fx1;
using enums::Moves::Dx1;
using enums::Moves::Lx1;
using enums::Moves::Bx1;

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

using enums::Colors::U;
using enums::Colors::D;

using cube333::kNMove;
using cube333::kNCornerPerm;
using cube333::kNCornerTwist;
using cube333::kNEdgePerm;
using cube333::kNEdgeFlip;
using cube333::kNSlicePosition;
using cube333::kCornerFaceletMap;
using cube333::kEdgeFaceletMap;
using cube333::kFaceletPerFace;
using cube333::kPhase2MoveCount;
using cube333::kPhase2Move;
using cube333::kNUd8EdgePerm;
using cube333::kNSliceEdgePerm;

using cube333::Edges::UF;
using cube333::Edges::UL;
using cube333::Edges::UB;
using cube333::Edges::UR;
using cube333::Edges::DF;
using cube333::Edges::DR;
using cube333::Edges::DB;
using cube333::Edges::DL;
using cube333::Edges::FL;
using cube333::Edges::BL;
using cube333::Edges::BR;
using cube333::Edges::FR;

using cube333::EdgeFlips::kNotFlipped;
using cube333::EdgeFlips::kFlipped;

using utils::getNPerm;
using utils::setNPerm;
using utils::getNFlip;
using utils::setNFlip;
using utils::getNParity;
using utils::setNComb4;
using utils::getNComb4;
using utils::randomizer;

CubieCube333::CubieCube333()
    : ep_ {UF, UL, UB, UR, DF, DR, DB, DL, FL, BL, BR, FR},
      eo_ {kNotFlipped} {}

CubieCube333::CubieCube333(const array<uint16_t, kNCorner> &cp,
                           const array<uint16_t, kNCorner> &co,
                           const array<uint16_t, kNEdge> &ep,
                           const array<uint16_t, kNEdge> &eo) {
  int twistsTotal = 0;
  int flipTotal = 0;
  uint16_t maskCorner = 0;
  uint16_t maskEdge = 0;

  for (auto i = 0; i < kNEdge; i++) {
    if (ep[i] > FR || (maskEdge & (1 << ep[i])) != 0) {
      throw invalid_argument("invalid edge permutation!");
    }
    maskEdge |= 1 << ep[i];
    if ((eo[i] & 0xfffe) != 0) {
      throw invalid_argument("invalid edge orientation!");
    }
    flipTotal ^= eo[i];

    if (i < kNCorner) {
      // (a & 0xfff8) != 0 is equivalent to a > 7 for uint16_t
      if ((cp[i] & 0xfff8) != 0 || (maskCorner & (1 << cp[i])) != 0) {
        throw invalid_argument("invalid corner permutation!");
      }
      maskCorner |= 1 << cp[i];
      if (co[i] < kOriented || co[i] > kCounterClockwise) {
        throw invalid_argument("invalid corner orientation!");
      }
      twistsTotal += co[i];
      cp_[i] = cp[i];
      co_[i] = co[i];
    }

    // assume all things are good, if we find something is wrong later,
    // we throw an exception
    ep_[i] = ep[i];
    eo_[i] = eo[i];
  }

  if ((flipTotal & 1) != 0) {
    throw invalid_argument("wrong edge orientation!");
  }

  if (twistsTotal % 3 != 0) {
    throw invalid_argument("wrong corner orientation!");
  }
}

CubieCube333::CubieCube333(uint16_t cp, uint16_t co, uint32_t ep, uint16_t eo) {
  if (cp >= kNCornerPerm || co >= kNCornerTwist ||
      ep >= kNEdgePerm || eo >= kNEdgeFlip) {
    throw invalid_argument("invalid parameters!");
  }
  setCP(cp);
  setCO(co);
  setEP(ep);
  setEO(eo);
}

void CubieCube333::setEP(uint32_t index) {
  setNPerm(&ep_, index, kNEdge);
}

void CubieCube333::setEO(uint16_t index) {
  setNFlip(&eo_, index, kNEdge);
}

void CubieCube333::setUD8EP(uint16_t index) {
  // we only care about the first 8 edges
  setNPerm(&ep_, index, 8);
  for (auto i = 8; i < kNEdge; i++) {
    ep_[i] = i;
  }
}

void CubieCube333::setSliceEP(uint16_t index) {
  // we only care about the last 4 edges
  setNPerm(&ep_, index, kNEdge);
}

void CubieCube333::setSlicePosition(uint16_t index) {
  setNComb4(&ep_, index, kNEdge, 0x8);
}

void CubieCube333::move(uint16_t move) {
  move %= kNMove;
  cubeMult(*this, getMoveCube(move), this);
}

uint32_t CubieCube333::getEPIndex() const {
  return getNPerm(ep_, kNEdge);
}

uint16_t CubieCube333::getEOIndex() const {
  return getNFlip(eo_, kNEdge);
}

uint16_t CubieCube333::getUD8EPIndex() const {
  return getNPerm(ep_, 8);
}

uint16_t CubieCube333::getSlicePositionIndex() const {
  return getNComb4(ep_, kNEdge, 0x8);
}

uint16_t CubieCube333::getSliceEPIndex() const {
  return getNPerm(ep_, kNEdge) % 24;
}

void CubieCube333::cubeMult(const CubieCube333 &one,
                            const CubieCube333 &another,
                            CubieCube333 *result) {
  auto cp = array<uint16_t, kNCorner>();
  auto co = array<uint16_t, kNCorner>();
  auto ep = array<uint16_t, kNEdge>();
  auto eo = array<uint16_t, kNEdge>();
  for (auto i = 0; i < kNCorner; i++) {
    cp[i] = one.cp_[another.cp_[i]];
    co[i] = (one.co_[another.cp_[i]] + another.co_[i]) % 3;
  }
  for (auto i = 0; i < kNEdge; i++) {
    ep[i] = one.ep_[another.ep_[i]];
    eo[i] = one.eo_[another.ep_[i]] ^ another.eo_[i];
  }
  result->cp_ = cp;
  result->co_ = co;
  result->ep_ = ep;
  result->eo_ = eo;
}

FaceletCubeNNN CubieCube333::toFaceletCube() const {
  auto f = vector<uint16_t>(kNFace * kFaceletPerFace);
  for (auto i = 0; i < kNFace; i++) {
    f[i * kFaceletPerFace + 4] = i;
  }
  for (auto i = 0; i < kNCorner; i++) {
    auto piece = cp_[i];
    auto orient = co_[i];
    for (auto j = 0; j < 3; j++) {
      f[kCornerFaceletMap[i][(j + orient) % 3]] =
          kCornerFaceletMap[piece][j] / kFaceletPerFace;
    }
  }
  for (auto i = 0; i < kNEdge; i++) {
    auto piece = ep_[i];
    auto orient = eo_[i];
    for (auto j = 0; j < 2; j++) {
      f[kEdgeFaceletMap[i][(j + orient) & 1]] =
          kEdgeFaceletMap[piece][j] / kFaceletPerFace;
    }
  }
  return FaceletCubeNNN(3, f);
}

CubieCube333 CubieCube333::fromFaceletCube(const FaceletCubeNNN &fc) {
  if (fc.getSize() != 3) {
    throw invalid_argument("needs a 3x3x3 cube!");
  }
  auto f = fc.getFacelets();
  array<uint16_t, kNCorner> cp;
  array<uint16_t, kNCorner> co;
  array<uint16_t, kNEdge> ep;
  array<uint16_t, kNEdge> eo;
  uint16_t color1, color2, ori;
  for (auto i = 0; i < kNCorner; i++) {
    for (ori = 0; ori < 3; ori++) {
      if (f[kCornerFaceletMap[i][ori]] == U ||
          f[kCornerFaceletMap[i][ori]] == D) {
        break;
      }
    }
    color1 = f[kCornerFaceletMap[i][(ori + 1) % 3]];
    color2 = f[kCornerFaceletMap[i][(ori + 2) % 3]];
    for (auto j = 0; j < kNCorner; j++) {
      if (color1 == kCornerFaceletMap[j][1] / kFaceletPerFace &&
          color2 == kCornerFaceletMap[j][2] / kFaceletPerFace) {
        cp[i] = j;
        co[i] = ori;
        break;
      }
    }
  }

  for (auto i = 0; i < kNEdge; i++) {
    for (auto j = 0; j < kNEdge; j++) {
      if ((f[kEdgeFaceletMap[i][0]] ==
              kEdgeFaceletMap[j][0] / kFaceletPerFace) &&
          (f[kEdgeFaceletMap[i][1]] ==
              kEdgeFaceletMap[j][1] / kFaceletPerFace)) {
        ep[i] = j;
        eo[i] = kNotFlipped;
      }
      if ((f[kEdgeFaceletMap[i][0]] ==
              kEdgeFaceletMap[j][1] / kFaceletPerFace) &&
          (f[kEdgeFaceletMap[i][1]] ==
              kEdgeFaceletMap[j][0] / kFaceletPerFace)) {
        ep[i] = j;
        eo[i] = kFlipped;
      }
    }
  }
  return CubieCube333(cp, co, ep, eo);
}

bool CubieCube333::isSolvable(uint16_t cpi, uint32_t epi) {
  uint16_t parity = getNParity(cpi, kNCorner);
  parity ^= getNParity(epi, kNEdge);
  return parity == 0;
}

CubieCube333 CubieCube333::randomCube() {
  auto rcp = randomizer(0, kNCornerPerm - 1);
  auto rep = randomizer(0, kNEdgePerm - 1);
  uint16_t cp;
  uint32_t ep;
  do {
    cp = rcp();
    ep = rep();
  } while (!isSolvable(cp, ep));
  auto r = randomizer(0, kNEdgeFlip * kNCornerTwist - 1);
  auto orient = r();
  return CubieCube333(cp, orient % kNCornerTwist,
    ep, orient / kNCornerTwist);
}

CubieCube333 CubieCube333::randomDRCube() {
  auto rcp = randomizer(0, kNCornerPerm - 1);
  auto rep1 = randomizer(0, kNUd8EdgePerm - 1);
  auto rep2 = randomizer(0, kNSliceEdgePerm - 1);
  array<uint16_t, 8> epArr1;
  array<uint16_t, 4> epArr2;
  array<uint16_t, kNEdge> epArr;
  uint16_t cp, ep1, ep2;
  uint32_t ep;
  do {
    cp = rcp();
    ep1 = rep1();
    ep2 = rep2();
    setNPerm(&epArr1, ep1, 8);
    setNPerm(&epArr2, ep2, 4);
    for (auto i = 0; i < kNEdge; i++) {
      if (i < 8) {
        epArr[i] = epArr1[i];
      } else {
        epArr[i] = epArr2[i - 8] + 8;
      }
    }
    ep = getNPerm(epArr, kNEdge);
  } while (!isSolvable(cp, ep));
  return CubieCube333(cp, 0, ep, 0);
}

string CubieCube333::toString() const {
  ostringstream os;
  os << "Corner Perms:";
  for (auto i = 0; i < kNCorner; i++) {
    os << " " << cp_[i];
  }
  os << endl << "Corner Twists:";
  for (auto i = 0; i < kNCorner; i++) {
    os << " " << co_[i];
  }
  os << endl << "Edge Perms:";
  for (auto i = 0; i < kNEdge; i++) {
    os << " " << ep_[i];
  }
  os << endl << "Edge Flips:";
  for (auto i = 0; i < kNEdge; i++) {
    os << " " << eo_[i];
  }
  os << endl;
  return os.str();
}

CubieCube333 CubieCube333::getMoveCube(uint16_t move) {
  static auto moveCubeTable = [] {
    auto ret = array<CubieCube333, kNMove>();
    ret[Ux1] = CubieCube333(
        {UBR, URF, UFL, ULB, DLF, DFR, DRB, DBL},
        {kOriented},
        {UR, UF, UL, UB, DF, DR, DB, DL, FL, BL, BR, FR},
        {kNotFlipped});
    ret[Rx1] = CubieCube333(
        {DFR, UFL, ULB, URF, DLF, DRB, UBR, DBL},
        {kCounterClockwise, kOriented, kOriented, kClockwise,
            kOriented, kClockwise, kCounterClockwise, kOriented},
        {UF, UL, UB, FR, DF, BR, DB, DL, FL, BL, UR, DR},
        {kNotFlipped});
    ret[Fx1] = CubieCube333(
        {UFL, DLF, ULB, UBR, DFR, URF, DRB, DBL},
        {kClockwise, kCounterClockwise, kOriented, kOriented,
            kClockwise, kCounterClockwise, kOriented, kOriented},
        {FL, UL, UB, UR, FR, DR, DB, DL, DF, BL, BR, UF},
        {kFlipped, kNotFlipped, kNotFlipped, kNotFlipped,
            kFlipped, kNotFlipped, kNotFlipped, kNotFlipped,
            kFlipped, kNotFlipped, kNotFlipped, kFlipped});
    ret[Dx1] = CubieCube333(
        {URF, UFL, ULB, UBR, DBL, DLF, DFR, DRB},
        {kOriented},
        {UF, UL, UB, UR, DL, DF, DR, DB, FL, BL, BR, FR},
        {kNotFlipped});
    ret[Lx1] = CubieCube333(
        {URF, ULB, DBL, UBR, UFL, DFR, DRB, DLF},
        {kOriented, kClockwise, kCounterClockwise, kOriented,
            kCounterClockwise, kOriented, kOriented, kClockwise},
        {UF, BL, UB, UR, DF, DR, DB, FL, UL, DL, BR, FR},
        {kNotFlipped});
    ret[Bx1] = CubieCube333(
        {URF, UFL, UBR, DRB, DLF, DFR, DBL, ULB},
        {kOriented, kOriented, kClockwise, kCounterClockwise,
            kOriented, kOriented, kClockwise, kCounterClockwise},
        {UF, UL, BR, UR, DF, DR, BL, DL, FL, UB, DB, FR},
        {kNotFlipped, kNotFlipped, kFlipped, kNotFlipped,
            kNotFlipped, kNotFlipped, kFlipped, kNotFlipped,
            kNotFlipped, kFlipped, kFlipped, kNotFlipped});

    for (auto i = 0; i < kNMove; i += kMovePerAxis) {
      for (auto j = 1; j < kMovePerAxis; j++) {
        ret[i + j] = CubieCube333();
        cubeMult(ret[i + j - 1], ret[i], &ret[i + j]);
      }
    }
    return ret;
  }();
  return moveCubeTable[move];
}

uint16_t CubieCube333::getFlipMove(uint16_t flip, uint16_t move) {
  static auto moveTable = [] {
    auto ret = array<array<uint16_t, kNMove>, kNEdgeFlip>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < kNEdgeFlip; i++) {
      c.setEO(i);
      for (auto j = 0; j < kNMove; j++) {
        cubeMult(c, getMoveCube(j), &d);
        ret[i][j] = d.getEOIndex();
      }
    }
    return ret;
  }();
  return moveTable[flip][move];
}

uint16_t CubieCube333::getTwistMove(uint16_t twist, uint16_t move) {
  static auto moveTable = [] {
    auto ret = array<array<uint16_t, kNMove>, kNCornerTwist>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < kNCornerTwist; i++) {
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

uint16_t CubieCube333::getSlicePositionMove(uint16_t slicePositionIndex,
  uint16_t move) {
  static auto moveTable = [] {
    auto ret = array<array<uint16_t, kNMove>, kNSlicePosition>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < kNSlicePosition; i++) {
      c.setSlicePosition(i);
      for (auto j = 0; j < kNMove; j++) {
        cubeMult(c, getMoveCube(j), &d);
        ret[i][j] = d.getSlicePositionIndex();
      }
    }
    return ret;
  }();
  return moveTable[slicePositionIndex][move];
}

uint16_t CubieCube333::getUD8EPMove(uint16_t ud8EP, uint16_t index) {
  static auto moveTable = [] {
    auto ret =
      array<array<uint16_t, kPhase2MoveCount>, kNUd8EdgePerm>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < kNUd8EdgePerm; i++) {
      c.setUD8EP(i);
      for (auto j = 0; j < kPhase2MoveCount; j++) {
        cubeMult(c, getMoveCube(kPhase2Move[j]), &d);
        ret[i][j] = d.getUD8EPIndex();
      }
    }
    return ret;
  }();
  return moveTable[ud8EP][index];
}

uint16_t CubieCube333::getSliceEPMove(uint16_t sliceEP, uint16_t index) {
  static auto moveTable = [] {
    array<array<uint16_t, kPhase2MoveCount>, kNSliceEdgePerm> ret;
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < kNSliceEdgePerm; i++) {
      c.setSliceEP(i);
      for (auto j = 0; j < kPhase2MoveCount; j++) {
        cubeMult(c, getMoveCube(kPhase2Move[j]), &d);
        ret[i][j] = d.getSliceEPIndex();
      }
    }
    return ret;
  }();
  return moveTable[sliceEP][index];
}

uint16_t CubieCube333::getCPMove(uint16_t cp, uint16_t index) {
  static auto moveTable = [] {
    auto ret =
      array<array<uint16_t, kPhase2MoveCount>, kNCornerPerm>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < kNCornerPerm; i++) {
      c.setCP(i);
      for (auto j = 0; j < kPhase2MoveCount; j++) {
        cubeMult(c, getMoveCube(kPhase2Move[j]), &d);
        ret[i][j] = d.getCPIndex();
      }
    }
    return ret;
  }();
  return moveTable[cp][index];
}

bool CubieCube333::operator==(const CubieCube333 &that) const {
  return getCPIndex() == that.getCPIndex() &&
         getCOIndex() == that.getCOIndex() &&
         getEPIndex() == that.getEPIndex() &&
         getEOIndex() == that.getEOIndex();
}

}  // namespace cube_util
