// Copyright 2019 Yunqi Ouyang
#define BOOST_TEST_MODULE scramble
#include<boost/test/unit_test.hpp>

#include<cube_util/MoveSequenceNNN.hpp>
#include<cube_util/Utils.hpp>

using std::vector;

using cube_util::MoveSequenceNNN;

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
using cube_util::enums::Moves::Uw1;
using cube_util::enums::Moves::Uw2;
using cube_util::enums::Moves::Uw3;
using cube_util::enums::Moves::Rw1;
using cube_util::enums::Moves::Rw2;
using cube_util::enums::Moves::Rw3;
using cube_util::enums::Moves::Fw1;
using cube_util::enums::Moves::Fw2;
using cube_util::enums::Moves::Fw3;
using cube_util::enums::Moves::Dw1;
using cube_util::enums::Moves::Dw2;
using cube_util::enums::Moves::Dw3;
using cube_util::enums::Moves::Lw1;
using cube_util::enums::Moves::Lw2;
using cube_util::enums::Moves::Lw3;
using cube_util::enums::Moves::Bw1;
using cube_util::enums::Moves::Bw2;
using cube_util::enums::Moves::Bw3;
using cube_util::enums::Moves::_3Uw1;
using cube_util::enums::Moves::_3Uw2;
using cube_util::enums::Moves::_3Uw3;
using cube_util::enums::Moves::_3Rw1;
using cube_util::enums::Moves::_3Rw2;
using cube_util::enums::Moves::_3Rw3;
using cube_util::enums::Moves::_3Fw1;
using cube_util::enums::Moves::_3Fw2;
using cube_util::enums::Moves::_3Fw3;
using cube_util::enums::Moves::_3Dw1;
using cube_util::enums::Moves::_3Dw2;
using cube_util::enums::Moves::_3Dw3;
using cube_util::enums::Moves::_3Lw1;
using cube_util::enums::Moves::_3Lw2;
using cube_util::enums::Moves::_3Lw3;
using cube_util::enums::Moves::_3Bw1;
using cube_util::enums::Moves::_3Bw2;
using cube_util::enums::Moves::_3Bw3;

BOOST_AUTO_TEST_SUITE(scramble)

BOOST_AUTO_TEST_CASE(test_parse_scramble) {
  auto str = "U2 R U F U2 R2 U' F R'";
  vector<uint16_t> exp = {Ux2, Rx1, Ux1, Fx1, Ux2, Rx2, Ux3, Fx1, Rx3};
  auto msn = MoveSequenceNNN(2, str);
  auto sequence = msn.getMoves();
  BOOST_REQUIRE_EQUAL(sequence.size(), exp.size());
  auto size = sequence.size();
  for (auto i = 0; i < size; i++) {
    BOOST_CHECK_EQUAL(sequence[i], exp[i]);
  }
  BOOST_CHECK_EQUAL(msn.toString(), str);
  BOOST_CHECK_EQUAL(msn.getLength(), 9);

  str = "F2 R2 U' B2 R2 D U2 B2 D2 U' B' U R U L' F' D' B' U L";
  exp = {
      Fx2, Rx2, Ux3, Bx2, Rx2, Dx1, Ux2, Bx2, Dx2, Ux3, Bx3, Ux1, Rx1, Ux1, Lx3,
      Fx3, Dx3, Bx3, Ux1, Lx1};
  msn = MoveSequenceNNN(3, str);
  sequence = msn.getMoves();
  BOOST_REQUIRE_EQUAL(sequence.size(), exp.size());
  size = sequence.size();
  for (auto i = 0; i < size; i++) {
    BOOST_CHECK_EQUAL(sequence[i], exp[i]);
  }
  BOOST_CHECK_EQUAL(msn.toString(), str);
  BOOST_CHECK_EQUAL(msn.getLength(), 20);

  str = "3Rw' Fw' Uw F' Uw' U' F 3Dw 3Fw 3Rw Uw2 R 3Dw' 3Bw' Fw U 3Uw2 3Fw2"
        " 3Uw2 Fw2 L2 3Lw Rw2 U Bw' L2 Dw' 3Fw 3Dw Fw' 3Rw 3Fw2 3Bw2 Fw 3Uw Dw"
        " Uw 3Lw' 3Bw' R' D2 U' R2 3Lw' Rw B Lw' F' 3Lw2 Dw Lw2 3Dw' Bw Fw'"
        " 3Dw' L 3Rw2 3Dw' 3Rw2 L' Dw' 3Dw2 B 3Bw2 F2 Uw 3Bw 3Fw Lw' Rw2 L2 Bw"
        " 3Dw R' Bw2 3Bw2 3Fw F' U Rw2 3Uw L D Dw2 Lw2 3Bw' Bw' Dw2 B2 Lw' B'"
        " 3Fw' 3Uw' Fw Dw2 D F U2 Rw' Fw'";
  exp = {
      _3Rw3, Fw3, Uw1, Fx3, Uw3, Ux3, Fx1, _3Dw1, _3Fw1, _3Rw1, Uw2, Rx1, _3Dw3,
      _3Bw3, Fw1, Ux1, _3Uw2, _3Fw2, _3Uw2, Fw2, Lx2, _3Lw1, Rw2, Ux1, Bw3, Lx2,
      Dw3, _3Fw1, _3Dw1, Fw3, _3Rw1, _3Fw2, _3Bw2, Fw1, _3Uw1, Dw1, Uw1, _3Lw3,
      _3Bw3, Rx3, Dx2, Ux3, Rx2, _3Lw3, Rw1, Bx1, Lw3, Fx3, _3Lw2, Dw1, Lw2,
      _3Dw3, Bw1, Fw3, _3Dw3, Lx1, _3Rw2, _3Dw3, _3Rw2, Lx3, Dw3, _3Dw2, Bx1,
      _3Bw2, Fx2, Uw1, _3Bw1, _3Fw1, Lw3, Rw2, Lx2, Bw1, _3Dw1, Rx3, Bw2, _3Bw2,
      _3Fw1, Fx3, Ux1, Rw2, _3Uw1, Lx1, Dx1, Dw2, Lw2, _3Bw3, Bw3, Dw2, Bx2,
      Lw3, Bx3, _3Fw3, _3Uw3, Fw1, Dw2, Dx1, Fx1, Ux2, Rw3, Fw3};
  msn = MoveSequenceNNN(7, str);
  sequence = msn.getMoves();
  BOOST_REQUIRE_EQUAL(sequence.size(), exp.size());
  size = sequence.size();
  for (auto i = 0; i < size; i++) {
    BOOST_CHECK_EQUAL(sequence[i], exp[i]);
  }
  BOOST_CHECK_EQUAL(msn.toString(), str);
  BOOST_CHECK_EQUAL(msn.getLength(), 100);
}

BOOST_AUTO_TEST_SUITE_END()
