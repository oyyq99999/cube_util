// Copyright 2019 Yunqi Ouyang
#include<cube_util/puzzle/CubieCube333.hpp>

#include<sstream>

namespace cube_util {

using std::invalid_argument;
using std::ostringstream;
using std::endl;

using constants::N_FACE;
using constants::N_MOVE_PER_AXIS;

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

using enums::CornerTwists::ORIENTED;
using enums::CornerTwists::CLOCKWISE;
using enums::CornerTwists::COUNTER_CLOCKWISE;

using enums::Colors::U;
using enums::Colors::D;

using cube333::N_MOVE;
using cube333::N_CORNER_PERM;
using cube333::N_CORNER_TWIST;
using cube333::N_EDGE_PERM;
using cube333::N_EDGE_FLIP;
using cube333::N_SLICE_POSITION;
using cube333::CORNER_FACELET_MAP;
using cube333::EDGE_FACELET_MAP;
using cube333::FACELET_PER_FACE;
using cube333::N_PHASE2_MOVE_COUNT;
using cube333::PHASE2_MOVE;
using cube333::N_UD8EDGE_PERM;
using cube333::N_SLICE_EDGE_PERM;

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

using cube333::EdgeFlips::NOT_FLIPPED;
using cube333::EdgeFlips::FLIPPED;

using utils::getNPerm;
using utils::setNPerm;
using utils::getNFlip;
using utils::setNFlip;
using utils::getNParity;
using utils::setNComb4;
using utils::getNComb4;
using utils::randomizer;

CubieCube333::CubieCube333()
    : ep {UF, UL, UB, UR, DF, DR, DB, DL, FL, BL, BR, FR},
      eo {NOT_FLIPPED} {}

CubieCube333::CubieCube333(const array<uint16_t, N_CORNER> &cp,
                           const array<uint16_t, N_CORNER> &co,
                           const array<uint16_t, N_EDGE> &ep,
                           const array<uint16_t, N_EDGE> &eo) {
  int twistsTotal = 0;
  int flipTotal = 0;
  uint16_t maskCorner = 0;
  uint16_t maskEdge = 0;

  for (auto i = 0; i < N_EDGE; i++) {
    if (ep[i] > FR || (maskEdge & (1 << ep[i])) != 0) {
      throw invalid_argument("invalid edge permutation!");
    }
    maskEdge |= 1 << ep[i];
    if ((eo[i] & 0xfffe) != 0) {
      throw invalid_argument("invalid edge orientation!");
    }
    flipTotal ^= eo[i];

    if (i < N_CORNER) {
      // (a & 0xfff8) != 0 is equivalent to a > 7 for uint16_t
      if ((cp[i] & 0xfff8) != 0 || (maskCorner & (1 << cp[i])) != 0) {
        throw invalid_argument("invalid corner permutation!");
      }
      maskCorner |= 1 << cp[i];
      if (co[i] < ORIENTED || co[i] > COUNTER_CLOCKWISE) {
        throw invalid_argument("invalid corner orientation!");
      }
      twistsTotal += co[i];
      this->cp[i] = cp[i];
      this->co[i] = co[i];
    }

    // assume all things are good, if we find something is wrong later,
    // we throw an exception
    this->ep[i] = ep[i];
    this->eo[i] = eo[i];
  }

  if ((flipTotal & 1) != 0) {
    throw invalid_argument("wrong edge orientation!");
  }

  if (twistsTotal % 3 != 0) {
    throw invalid_argument("wrong corner orientation!");
  }
}

CubieCube333::CubieCube333(uint16_t cp, uint16_t co, uint32_t ep, uint16_t eo) {
  if (cp >= N_CORNER_PERM || co >= N_CORNER_TWIST ||
      ep >= N_EDGE_PERM || eo >= N_EDGE_FLIP) {
    throw invalid_argument("invalid parameters!");
  }
  this->setCP(cp);
  this->setCO(co);
  this->setEP(ep);
  this->setEO(eo);
}

void CubieCube333::setEP(uint32_t index) {
  setNPerm(&ep, index, N_EDGE);
}

void CubieCube333::setEO(uint16_t index) {
  setNFlip(&eo, index, N_EDGE);
}

void CubieCube333::setUD8EP(uint16_t index) {
  // we only care about the first 8 edges
  setNPerm(&ep, index, 8);
  for (auto i = 8; i < N_EDGE; i++) {
    ep[i] = i;
  }
}

void CubieCube333::setSliceEP(uint16_t index) {
  // we only care about the last 4 edges
  setNPerm(&ep, index, N_EDGE);
}

void CubieCube333::setSlicePosition(uint16_t index) {
  setNComb4(&ep, index, N_EDGE, 0x8);
}

void CubieCube333::move(uint16_t move) {
  move %= N_MOVE;
  cubeMult(*this, getMoveCube(move), this);
}

uint32_t CubieCube333::getEPIndex() const {
  return getNPerm(ep, N_EDGE);
}

uint16_t CubieCube333::getEOIndex() const {
  return getNFlip(eo, N_EDGE);
}

uint16_t CubieCube333::getUD8EPIndex() const {
  return getNPerm(ep, 8);
}

uint16_t CubieCube333::getSlicePositionIndex() const {
  return getNComb4(ep, N_EDGE, 0x8);
}

uint16_t CubieCube333::getSliceEPIndex() const {
  return getNPerm(ep, N_EDGE) % 24;
}

void CubieCube333::cubeMult(const CubieCube333 &one,
                            const CubieCube333 &another,
                            CubieCube333 *result) {
  auto cp = array<uint16_t, N_CORNER>();
  auto co = array<uint16_t, N_CORNER>();
  auto ep = array<uint16_t, N_EDGE>();
  auto eo = array<uint16_t, N_EDGE>();
  for (auto i = 0; i < N_CORNER; i++) {
    cp[i] = one.cp[another.cp[i]];
    co[i] = (one.co[another.cp[i]] + another.co[i]) % 3;
  }
  for (auto i = 0; i < N_EDGE; i++) {
    ep[i] = one.ep[another.ep[i]];
    eo[i] = one.eo[another.ep[i]] ^ another.eo[i];
  }
  result->cp = cp;
  result->co = co;
  result->ep = ep;
  result->eo = eo;
}

FaceletCubeNNN CubieCube333::toFaceletCube() const {
  auto f = vector<uint16_t>(N_FACE * FACELET_PER_FACE);
  for (auto i = 0; i < N_FACE; i++) {
    f[i * FACELET_PER_FACE + 4] = i;
  }
  for (auto i = 0; i < N_CORNER; i++) {
    auto piece = cp[i];
    auto orient = co[i];
    for (auto j = 0; j < 3; j++) {
      f[CORNER_FACELET_MAP[i][(j + orient) % 3]] =
          CORNER_FACELET_MAP[piece][j] / FACELET_PER_FACE;
    }
  }
  for (auto i = 0; i < N_EDGE; i++) {
    auto piece = ep[i];
    auto orient = eo[i];
    for (auto j = 0; j < 2; j++) {
      f[EDGE_FACELET_MAP[i][(j + orient) & 1]] =
          EDGE_FACELET_MAP[piece][j] / FACELET_PER_FACE;
    }
  }
  return FaceletCubeNNN(3, f);
}

CubieCube333 CubieCube333::fromFaceletCube(const FaceletCubeNNN &fc) {
  if (fc.getSize() != 3) {
    throw invalid_argument("needs a 3x3x3 cube!");
  }
  auto f = fc.getFacelets();
  array<uint16_t, N_CORNER> cp;
  array<uint16_t, N_CORNER> co;
  array<uint16_t, N_EDGE> ep;
  array<uint16_t, N_EDGE> eo;
  uint16_t color1, color2, ori;
  for (auto i = 0; i < N_CORNER; i++) {
    for (ori = 0; ori < 3; ori++) {
      if (f[CORNER_FACELET_MAP[i][ori]] == U ||
          f[CORNER_FACELET_MAP[i][ori]] == D) {
        break;
      }
    }
    color1 = f[CORNER_FACELET_MAP[i][(ori + 1) % 3]];
    color2 = f[CORNER_FACELET_MAP[i][(ori + 2) % 3]];
    for (auto j = 0; j < N_CORNER; j++) {
      if (color1 == CORNER_FACELET_MAP[j][1] / FACELET_PER_FACE &&
          color2 == CORNER_FACELET_MAP[j][2] / FACELET_PER_FACE) {
        cp[i] = j;
        co[i] = ori;
        break;
      }
    }
  }

  for (auto i = 0; i < N_EDGE; i++) {
    for (auto j = 0; j < N_EDGE; j++) {
      if ((f[EDGE_FACELET_MAP[i][0]] ==
              EDGE_FACELET_MAP[j][0] / FACELET_PER_FACE) &&
          (f[EDGE_FACELET_MAP[i][1]] ==
              EDGE_FACELET_MAP[j][1] / FACELET_PER_FACE)) {
        ep[i] = j;
        eo[i] = NOT_FLIPPED;
      }
      if ((f[EDGE_FACELET_MAP[i][0]] ==
              EDGE_FACELET_MAP[j][1] / FACELET_PER_FACE) &&
          (f[EDGE_FACELET_MAP[i][1]] ==
              EDGE_FACELET_MAP[j][0] / FACELET_PER_FACE)) {
        ep[i] = j;
        eo[i] = FLIPPED;
      }
    }
  }
  return CubieCube333(cp, co, ep, eo);
}

bool CubieCube333::isSolvable(uint16_t cpi, uint32_t epi) {
  uint16_t parity = getNParity(cpi, N_CORNER);
  parity ^= getNParity(epi, N_EDGE);
  return parity == 0;
}

CubieCube333 CubieCube333::randomCube() {
  auto rcp = randomizer(0, N_CORNER_PERM - 1);
  auto rep = randomizer(0, N_EDGE_PERM - 1);
  uint16_t cp;
  uint32_t ep;
  do {
    cp = rcp();
    ep = rep();
  } while (!isSolvable(cp, ep));
  auto r = randomizer(0, N_EDGE_FLIP * N_CORNER_TWIST - 1);
  auto orient = r();
  return CubieCube333(cp, orient % N_CORNER_TWIST,
    ep, orient / N_CORNER_TWIST);
}

CubieCube333 CubieCube333::randomDRCube() {
  auto rcp = randomizer(0, N_CORNER_PERM - 1);
  auto rep1 = randomizer(0, N_UD8EDGE_PERM - 1);
  auto rep2 = randomizer(0, N_SLICE_EDGE_PERM - 1);
  array<uint16_t, 8> epArr1;
  array<uint16_t, 4> epArr2;
  array<uint16_t, N_EDGE> epArr;
  uint16_t cp, ep1, ep2;
  uint32_t ep;
  do {
    cp = rcp();
    ep1 = rep1();
    ep2 = rep2();
    setNPerm(&epArr1, ep1, 8);
    setNPerm(&epArr2, ep2, 4);
    for (auto i = 0; i < N_EDGE; i++) {
      if (i < 8) {
        epArr[i] = epArr1[i];
      } else {
        epArr[i] = epArr2[i - 8] + 8;
      }
    }
    ep = getNPerm(epArr, N_EDGE);
  } while (!isSolvable(cp, ep));
  return CubieCube333(cp, 0, ep, 0);
}

string CubieCube333::toString() const {
  ostringstream os;
  os << "Corner Perms:";
  for (auto i = 0; i < N_CORNER; i++) {
    os << " " << cp[i];
  }
  os << endl << "Corner Twists:";
  for (auto i = 0; i < N_CORNER; i++) {
    os << " " << co[i];
  }
  os << endl << "Edge Perms:";
  for (auto i = 0; i < N_EDGE; i++) {
    os << " " << ep[i];
  }
  os << endl << "Edge Flips:";
  for (auto i = 0; i < N_EDGE; i++) {
    os << " " << eo[i];
  }
  os << endl;
  return os.str();
}

CubieCube333 CubieCube333::getMoveCube(uint16_t move) {
  static auto moveCubeTable = [] {
    auto ret = array<CubieCube333, N_MOVE>();
    ret[Ux1] = CubieCube333(
        {UBR, URF, UFL, ULB, DLF, DFR, DRB, DBL},
        {ORIENTED},
        {UR, UF, UL, UB, DF, DR, DB, DL, FL, BL, BR, FR},
        {NOT_FLIPPED});
    ret[Rx1] = CubieCube333(
        {DFR, UFL, ULB, URF, DLF, DRB, UBR, DBL},
        {COUNTER_CLOCKWISE, ORIENTED, ORIENTED, CLOCKWISE,
            ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED},
        {UF, UL, UB, FR, DF, BR, DB, DL, FL, BL, UR, DR},
        {NOT_FLIPPED});
    ret[Fx1] = CubieCube333(
        {UFL, DLF, ULB, UBR, DFR, URF, DRB, DBL},
        {CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED, ORIENTED,
            CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED, ORIENTED},
        {FL, UL, UB, UR, FR, DR, DB, DL, DF, BL, BR, UF},
        {FLIPPED, NOT_FLIPPED, NOT_FLIPPED, NOT_FLIPPED,
            FLIPPED, NOT_FLIPPED, NOT_FLIPPED, NOT_FLIPPED,
            FLIPPED, NOT_FLIPPED, NOT_FLIPPED, FLIPPED});
    ret[Dx1] = CubieCube333(
        {URF, UFL, ULB, UBR, DBL, DLF, DFR, DRB},
        {ORIENTED},
        {UF, UL, UB, UR, DL, DF, DR, DB, FL, BL, BR, FR},
        {NOT_FLIPPED});
    ret[Lx1] = CubieCube333(
        {URF, ULB, DBL, UBR, UFL, DFR, DRB, DLF},
        {ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED,
            COUNTER_CLOCKWISE, ORIENTED, ORIENTED, CLOCKWISE},
        {UF, BL, UB, UR, DF, DR, DB, FL, UL, DL, BR, FR},
        {NOT_FLIPPED});
    ret[Bx1] = CubieCube333(
        {URF, UFL, UBR, DRB, DLF, DFR, DBL, ULB},
        {ORIENTED, ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE,
            ORIENTED, ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE},
        {UF, UL, BR, UR, DF, DR, BL, DL, FL, UB, DB, FR},
        {NOT_FLIPPED, NOT_FLIPPED, FLIPPED, NOT_FLIPPED,
            NOT_FLIPPED, NOT_FLIPPED, FLIPPED, NOT_FLIPPED,
            NOT_FLIPPED, FLIPPED, FLIPPED, NOT_FLIPPED});

    for (auto i = 0; i < N_MOVE; i += N_MOVE_PER_AXIS) {
      for (auto j = 1; j < N_MOVE_PER_AXIS; j++) {
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
    auto ret = array<array<uint16_t, N_MOVE>, N_EDGE_FLIP>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < N_EDGE_FLIP; i++) {
      c.setEO(i);
      for (auto j = 0; j < N_MOVE; j++) {
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
    auto ret = array<array<uint16_t, N_MOVE>, N_CORNER_TWIST>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < N_CORNER_TWIST; i++) {
      c.setCO(i);
      for (auto j = 0; j < N_MOVE; j++) {
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
    auto ret = array<array<uint16_t, N_MOVE>, N_SLICE_POSITION>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < N_SLICE_POSITION; i++) {
      c.setSlicePosition(i);
      for (auto j = 0; j < N_MOVE; j++) {
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
      array<array<uint16_t, N_PHASE2_MOVE_COUNT>, N_UD8EDGE_PERM>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < N_UD8EDGE_PERM; i++) {
      c.setUD8EP(i);
      for (auto j = 0; j < N_PHASE2_MOVE_COUNT; j++) {
        cubeMult(c, getMoveCube(PHASE2_MOVE[j]), &d);
        ret[i][j] = d.getUD8EPIndex();
      }
    }
    return ret;
  }();
  return moveTable[ud8EP][index];
}

uint16_t CubieCube333::getSliceEPMove(uint16_t sliceEP, uint16_t index) {
  static auto moveTable = [] {
    array<array<uint16_t, N_PHASE2_MOVE_COUNT>, N_SLICE_EDGE_PERM> ret;
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < N_SLICE_EDGE_PERM; i++) {
      c.setSliceEP(i);
      for (auto j = 0; j < N_PHASE2_MOVE_COUNT; j++) {
        cubeMult(c, getMoveCube(PHASE2_MOVE[j]), &d);
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
      array<array<uint16_t, N_PHASE2_MOVE_COUNT>, N_CORNER_PERM>();
    CubieCube333 c = CubieCube333();
    CubieCube333 d = CubieCube333();
    for (auto i = 0; i < N_CORNER_PERM; i++) {
      c.setCP(i);
      for (auto j = 0; j < N_PHASE2_MOVE_COUNT; j++) {
        cubeMult(c, getMoveCube(PHASE2_MOVE[j]), &d);
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
