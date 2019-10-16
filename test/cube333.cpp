// Copyright 2019 Yunqi Ouyang
#define BOOST_TEST_MODULE cube333
#include <boost/test/unit_test.hpp>

#include "cube_util/puzzle/cubie_cube_333.hpp"
#include "cube_util/cube_333_solver.hpp"

using cube_util::FaceletCubeNNN;
using cube_util::CubieCube333;
using cube_util::Cube333Solver;

using cube_util::enums::Moves::Ux1;
using cube_util::enums::Moves::Ux2;
using cube_util::enums::Moves::Ux3;
using cube_util::enums::Moves::Rx1;
using cube_util::enums::Moves::Rx2;
using cube_util::enums::Moves::Rx3;
using cube_util::enums::Moves::Fx1;
using cube_util::enums::Moves::Fx2;
using cube_util::enums::Moves::Fx3;
using cube_util::enums::Moves::Dx1;
using cube_util::enums::Moves::Dx2;
using cube_util::enums::Moves::Dx3;
using cube_util::enums::Moves::Lx1;
using cube_util::enums::Moves::Lx2;
using cube_util::enums::Moves::Lx3;
using cube_util::enums::Moves::Bx1;
using cube_util::enums::Moves::Bx2;
using cube_util::enums::Moves::Bx3;

using cube_util::cube333::kPhase2MoveCount;
using cube_util::cube333::kPhase2Move;

BOOST_AUTO_TEST_SUITE(cube333)

BOOST_AUTO_TEST_CASE(test_cube333) {
  FaceletCubeNNN ifc = FaceletCubeNNN(3);
  FaceletCubeNNN fc = FaceletCubeNNN(3);
  fc.moveF(9);
  fc.moveR(2);
  fc.moveU(3);
  fc.moveD(9);
  fc.moveB(2);
  fc.moveR(2);
  fc.moveF(1);
  fc.moveL(2);
  auto ftc = CubieCube333::fromFaceletCube(fc);
  CubieCube333 cc;
  cc.move(Fx1);
  cc.move(Rx2);
  cc.move(Ux3);
  cc.move(Dx1);
  cc.move(Bx2);
  cc.move(Rx2);
  cc.move(Fx1);
  cc.move(Lx2);
  BOOST_CHECK_EQUAL(ftc, cc);

  cc = CubieCube333();
  // test moves: F' B U2 B R F U' F' U F' D2 B' L2 U2 R2 F L2 B L2
  auto moves = {Fx3, Bx1, Ux2, Bx1, Rx1, Fx1, Ux3, Fx3, Ux1, Fx3, Dx2, Bx3, Lx2,
                Ux2, Rx2, Fx1, Lx2, Bx1, Lx2};
  for (auto move : moves) {
    cc.move(move);
  }
  fc = cc.toFaceletCube();
  // reverse moves with facelet cube model
  fc.moveL(2);
  fc.moveB(3);
  fc.moveL(2);
  fc.moveF(3);
  fc.moveR(2);
  fc.moveU(2);
  fc.moveL(2);
  fc.moveB(1);
  fc.moveD(2);
  fc.moveF(1);
  fc.moveU(3);
  fc.moveF(1);
  fc.moveU(1);
  fc.moveF(3);
  fc.moveR(3);
  fc.moveB(3);
  fc.moveU(2);
  fc.moveB(3);
  fc.moveF(1);
  BOOST_CHECK(ifc.getFacelets() == fc.getFacelets());

  cc = CubieCube333();
  cc.move(Rx3);
  cc.move(Ux3);
  cc.move(Fx1);
  cc.move(Dx2);
  cc.move(Lx3);
  cc.move(Bx2);
  auto expc = CubieCube333(13037, 955, 334956095U, 1792);
  BOOST_CHECK_EQUAL(cc, expc);
}

BOOST_AUTO_TEST_CASE(test_333_phase2_move_tables) {
  const auto N = 10000;
  for (auto i = 0; i < N; i++) {
    auto cc1 = CubieCube333::randomDRCube();
    auto cp1 = cc1.getCPIndex();
    auto ud8EP1 = cc1.getUD8EPIndex();
    auto sliceEP1 = cc1.getSliceEPIndex();
    for (auto j = 0; j < kPhase2MoveCount; j++) {
      auto cc2 = CubieCube333(cc1);
      cc2.move(kPhase2Move[j]);
      BOOST_CHECK_EQUAL(CubieCube333::getCPMove(cp1, j), cc2.getCPIndex());
      BOOST_CHECK_EQUAL(CubieCube333::getUD8EPMove(ud8EP1, j),
                        cc2.getUD8EPIndex());
      BOOST_CHECK_EQUAL(CubieCube333::getSliceEPMove(sliceEP1, j),
                        cc2.getSliceEPIndex());
    }
  }
}

BOOST_AUTO_TEST_CASE(test_333_solver) {
  CubieCube333 cc;
  // test moves: F' B U2 B R F U' F' U F' D2 // B' L2 U2 R2 F L2 B L2
  auto moves = {Fx3, Bx1, Ux2, Bx1, Rx1, Fx1, Ux3, Fx3, Ux1, Fx3, Dx2};
  for (auto move : moves) {
    cc.move(move);
  }
  auto solver = Cube333Solver(cc);
  BOOST_CHECK_EQUAL(solver.isSolvableIn(10), false);
  BOOST_CHECK_EQUAL(solver.isSolvableIn(11), true);

  const auto N = 100;
  const CubieCube333 idc;
  for (auto i = 0; i < N; i++) {
    auto cc1 = CubieCube333::randomCube();
    auto solver = Cube333Solver(cc1);
    auto g = solver.generate();
    CubieCube333 cc2;
    for (auto m : g->getMoves()) {
      cc2.move(m);
    }
    BOOST_CHECK_EQUAL(cc1, cc2);
    auto s = solver.solve(21);
    for (auto m : s->getMoves()) {
      cc2.move(m);
    }
    BOOST_CHECK_EQUAL(cc2, idc);
  }
}

BOOST_AUTO_TEST_SUITE_END()
