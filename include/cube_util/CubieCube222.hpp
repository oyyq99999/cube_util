#ifndef CUBIE_CUBE222_HPP
#define CUBIE_CUBE222_HPP
#include<iostream>
#include<array>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    using namespace constants;

    ////////////////////////////////////////////////////////////////////////////
    /// A class representing a 2x2x2 cube model by cubie level.
    /// It declares corner permutations in this order: `URF`, `UFL`, `ULB`,
    /// `UBR`, `DLF`, `DFR`, `DRB`, `DBL`. <br>
    /// It declares corner orientations in the same order with these numbers:
    /// - 0 means **oriented**;
    /// - 1 means **clockwise** twisted once from the **oriented** status;
    /// - 2 means **counter-clockwise** twisted.
    ///
    /// Currently the last one (perm[7] needs to be the `DBL` corner) and the
    /// twist of it needs to be `0` (oriented).
    ////////////////////////////////////////////////////////////////////////////
    class CubieCube222 {

        /** Permutations of the cubies. */
        array<uint16_t, N_CORNERS> perm;

        /** Orientations of the cubies. */
        array<uint16_t, N_CORNERS> twist;

        /**
         * Outputs info about the cube, includes perms and twists
         */
        friend ostream& operator<<(ostream& os, const CubieCube222 &cc);

        /**
         * Table representing moves applied to an identity cube,
         * used to calculate new cube states.
         */
        static const array<CubieCube222, cube_util::cube222::N_MOVE> MOVE_CUBES;

        /**
         * Calculate product (_one_ * _another_) of two cubes.
         * @param[in] one the first cube
         * @param[in] another the second cube
         * @param[out] result cube to return the result to
         */
        static void cubeMult(CubieCube222 one, CubieCube222 another, CubieCube222 &result);

    public:
        CubieCube222();

        /**
         * Constructor of the class.
         * @param perm permutations to initialize with
         * @param twist orientations to initialize with
         */
        CubieCube222(array<uint16_t, N_CORNERS> perm, array<uint16_t, N_CORNERS> twist);

        /**
         * Apply move to the current cube.
         * @param move the move to apply, as described in cube_util::constants
         */
        void move(int move);
    };

}

#endif // CUBIE_CUBE222_HPP
