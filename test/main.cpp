#define BOOST_TEST_MODULE cube_util
#include<regex>
#include<boost/test/unit_test.hpp>
#include<cube_util/FaceletCubeNNN.hpp>
#include<cube_util/CubieCube222.hpp>
#include<cube_util/Cube222Solver.hpp>
#include<cube_util/Utils.hpp>

using namespace std;
using namespace cube_util;
using namespace cube_util::utils;

BOOST_AUTO_TEST_SUITE(cube_model)

BOOST_AUTO_TEST_CASE(test_faceletcube) {
    auto fc = FaceletCubeNNN(3);
    fc.moveR(3);
    fc.moveU(3);
    fc.moveF();
    fc.moveDw(1);
    fc.moveL(2);
    fc.moveB();
    vector<uint16_t> exp = {
        U, L, L, D, U, U, F, L, B,
        U, F, F, F, F, F, U, U, L,
        R, F, L, R, L, D, R, L, F,
        B, D, R, U, D, R, B, B, D,
        B, B, D, B, B, D, D, B, D,
        U, U, R, R, R, R, F, L, L,
    };
    BOOST_CHECK(fc.getFacelets() == exp);
}

BOOST_AUTO_TEST_CASE(test_cube222) {
    FaceletCubeNNN ifc = FaceletCubeNNN(2);
    FaceletCubeNNN fc = FaceletCubeNNN(2);
    fc.moveF(9);
    fc.moveR(2);
    fc.moveU(3);
    auto ftc = CubieCube222::fromFaceletCube(fc);
    CubieCube222 cc;
    cc.move(Fx1);
    cc.move(Rx2);
    cc.move(Ux3);
    BOOST_CHECK_EQUAL(ftc.getCP(), cc.getCP());
    BOOST_CHECK_EQUAL(ftc.getCO(), cc.getCO());

    cc = CubieCube222();
    // test moves: U2 R U F U2 R2 U' F R'
    auto moves = {Ux2, Rx1, Ux1, Fx1, Ux2, Rx2, Ux3, Fx1, Rx3};
    for (auto move : moves) {
        cc.move(move);
    }
    fc = cc.toFaceletCube();
    // reverse moves with facelet cube model
    fc.moveR();
    fc.moveF(3);
    fc.moveU();
    fc.moveR(2);
    fc.moveU(2);
    fc.moveF(3);
    fc.moveU(3);
    fc.moveR(3);
    fc.moveU(2);
    BOOST_CHECK(ifc.getFacelets() == fc.getFacelets());

    auto solver = Cube222Solver(cc);
    BOOST_CHECK(!solver.isSolvableIn(6));
    BOOST_CHECK(!solver.isSolvableIn(8));
    BOOST_CHECK(solver.isSolvableIn(9));
    BOOST_CHECK(solver.isSolvableIn(11));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(utils)

BOOST_AUTO_TEST_CASE(test_cycle4) {
    vector<uint16_t> v = {3, 5, 7, 1, 6, 0, 8, 2};
    cycle4(v, 3, 7, 2, 5);
    ostringstream os;
    for (auto e : v) {
        os << e;
    }
    BOOST_CHECK_EQUAL(os.str(), "35206781");
}

BOOST_AUTO_TEST_CASE(test_getSetNPerm) {
    array<uint16_t, 5> arr1 = {0, 1, 2, 3, 4};
    auto i = getNPerm(arr1, 5);
    BOOST_CHECK_EQUAL(i, 0);
    setNPerm(arr1, i + 1, 5);
    array<uint16_t, 5> exp1 = {0, 1, 2, 4, 3};
    BOOST_CHECK(arr1 == exp1);

    array<uint16_t, 12> arr2 = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    BOOST_CHECK_EQUAL(getNPerm(arr2, 12), 39916800); // 11!
    BOOST_CHECK_EQUAL(getNPerm(arr2, 5), 24);

    array<uint16_t, 12> arr3 = {3, 2, 4, 1, 0};
    BOOST_CHECK_EQUAL(getNPerm(arr3, 5), 89);
}

BOOST_AUTO_TEST_CASE(test_getSetNTwist) {
    array<uint16_t, 5> arr1 = {0, 1, 2, 0, 0};
    auto i = getNTwist(arr1, 5);
    BOOST_CHECK_EQUAL(i, 15);
    setNTwist(arr1, i + 1, 5);
    array<uint16_t, 5> exp1 = {0, 1, 2, 1, 2};
    BOOST_CHECK(arr1 == exp1);
}

BOOST_AUTO_TEST_CASE(test_scramble) {
    auto re2 = regex("^[URF][2']?( [URF][2']?){10}$");
    auto re3 = regex("^[URFDLB][2']?( [URFDLB][2']?){24}$");
    auto re4 = regex("^([URF]w?|[DLB])[2']?( ([URF]w?|[DLB])[2']?){39}$");
    auto re5 = regex("^[URFDLB]w?[2']?( ([URFDLB]w?[2']?)){59}$");
    auto re6 = regex("^([URFDLB]w?|3[URF]w)[2']?( ([URFDLB]w?|3[URF]w)[2']?){79}$");
    auto re7 = regex("^([URFDLB]w?|3[URFDLB]w)[2']?( ([URFDLB]w?|3[URFDLB]w)[2']?){99}$");

    auto scr = scrambleString(2);
    BOOST_CHECK(regex_match(scr, re2));
    scr = scrambleString(3);
    BOOST_CHECK(regex_match(scr, re3));
    scr = scrambleString(4);
    BOOST_CHECK(regex_match(scr, re4));
    scr = scrambleString(5);
    BOOST_CHECK(regex_match(scr, re5));
    scr = scrambleString(6);
    BOOST_CHECK(regex_match(scr, re6));
    scr = scrambleString(7);
    BOOST_CHECK(regex_match(scr, re7));
}

BOOST_AUTO_TEST_SUITE_END()