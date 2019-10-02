// Copyright 2019 Yunqi Ouyang
#include<cube_util/CubieCube333.hpp>

namespace cube_util {

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

    using constants::N_MOVE_PER_AXIS;

    const array<CubieCube333, N_MOVE> CubieCube333::MOVE_CUBES = [] {
        auto ret = array<CubieCube333, N_MOVE>();
        ret[Ux1] = CubieCube333({UBR, URF, UFL, ULB, DLF, DFR, DRB, DBL},
            {ORIENTED}, {UR, UF, UL, UB, DF, DR, DB, DL, FL, BL, BR, FR},
            {NOT_FLIPPED});
        ret[Rx1] = CubieCube333({DFR, UFL, ULB, URF, DLF, DRB, UBR, DBL},
            {COUNTER_CLOCKWISE, ORIENTED, ORIENTED, CLOCKWISE, ORIENTED,
                CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED},
            {UF, UL, UB, FR, DF, BR, DB, DL, FL, BL, UR, DR},
            {NOT_FLIPPED});
        ret[Fx1] = CubieCube333({UFL, DLF, ULB, UBR, DFR, URF, DRB, DBL},
            {CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED, ORIENTED, CLOCKWISE,
                COUNTER_CLOCKWISE, ORIENTED, ORIENTED},
            {FL, UL, UB, UR, FR, DR, DB, DL, DF, BL, BR, UF},
            {FLIPPED, NOT_FLIPPED, NOT_FLIPPED, NOT_FLIPPED, FLIPPED,
                NOT_FLIPPED, NOT_FLIPPED, NOT_FLIPPED, FLIPPED, NOT_FLIPPED,
                NOT_FLIPPED, FLIPPED});
        ret[Dx1] = CubieCube333({URF, UFL, ULB, UBR, DBL, DLF, DFR, DRB},
            {ORIENTED}, {UF, UL, UB, UR, DL, DF, DR, DB, FL, BL, BR, FR},
            {NOT_FLIPPED});
        ret[Lx1] = CubieCube333({URF, ULB, DBL, UBR, UFL, DFR, DRB, DLF},
            {ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED,
                COUNTER_CLOCKWISE, ORIENTED, ORIENTED, CLOCKWISE},
            {UF, BL, UB, UR, DF, DR, DB, FL, UL, DL, BR, FR},
            {NOT_FLIPPED});
        ret[Bx1] = CubieCube333({URF, UFL, UBR, DRB, DLF, DFR, DBL, ULB},
            {ORIENTED, ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE, ORIENTED,
                ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE},
            {UF, UL, BR, UR, DF, DR, BL, DL, FL, UB, DB, FR},
            {NOT_FLIPPED, NOT_FLIPPED, FLIPPED, NOT_FLIPPED, NOT_FLIPPED,
                NOT_FLIPPED, FLIPPED, NOT_FLIPPED, NOT_FLIPPED, FLIPPED,
                FLIPPED, NOT_FLIPPED});

        for (auto i = 0; i < N_MOVE; i += N_MOVE_PER_AXIS) {
            for (auto j = 1; j < N_MOVE_PER_AXIS; j++) {
                ret[i + j] = CubieCube333();
                cubeMult(ret[i + j - 1], ret[i], &ret[i + j]);
            }
        }
        return ret;
    }();

}  // namespace cube_util
