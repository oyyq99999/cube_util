#ifndef CUBIE_CUBE222_HPP
#define CUBIE_CUBE222_HPP
#include<iostream>
#include<array>
#include<cube_util/FaceletCubeNNN.hpp>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    using namespace constants;
    using namespace cube222;

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
        array<uint16_t, N_CORNER> perm;

        /** Orientations of the cubies. */
        array<uint16_t, N_CORNER> twist;

        /**
         * Outputs info about the cube, includes perms and twists
         */
        friend ostream& operator<<(ostream& os, const CubieCube222 &cc);

        /**
         * Set permutation state according to given index.
         * @param index specified index
         */
        void setPerm(uint64_t index);

        /**
         * Set orientation state according to given index.
         * @param index specified index
         */
        void setTwist(uint16_t);


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
        CubieCube222(array<uint16_t, N_CORNER> perm, array<uint16_t, N_CORNER> twist);

        /**
         * Constructor of the class.
         * @param perm permutation index to initialize with
         * @param twist orientation index to initialize with
         */
        CubieCube222(uint16_t perm, uint16_t twist);

        /**
         * Constructor of the class.
         * `index` = `perm` * `N_TWIST` + `twist`
         * @param index index to initialize with
         */
        CubieCube222(uint32_t index);

        /**
         * Apply move to the current cube.
         * @param move the move to apply, as described in cube_util::constants
         */
        void move(int move);

        /**
         * Calculate permutation index of current state.
         */
        uint64_t getPerm();

        /**
         * Calculate orientation index of current state.
         */
        uint16_t getTwist();

        /**
         * Create a FaceletCubeNNN based on the CubieCube222.
         * @returns a FaceletCubeNNN instance with a size of 2
         */
        FaceletCubeNNN toFaceletCube();

        /**
         * Create a CubieCube222 based on a FaceletCubeNNN.
         * @param fc a FaceletCubeNNN with a size of 2
         * @returns a CubieCube222 instance
         */
        static CubieCube222 fromFaceletCube(FaceletCubeNNN fc);

        /**
         * Get a cube in random position.
         * @returns a CubbieCube222 with random state
         */
        static CubieCube222 randomCube();

        /**
         * Table representing moves applied to an identity cube,
         * used to calculate new cube states.
         */
        static const array<CubieCube222, N_MOVE> MOVE_CUBES;

        /**
         * Table representing new permutation coordinate by applying a move to
         * specified permutation coordinate.
         */
        static const array<array<uint16_t, N_MOVE>, N_PERM> PERM_MOVE;

        /**
         * Table representing new orientation coordinate by applying a move to
         * specified orientation coordinate.
         */
        static const array<array<uint16_t, N_MOVE>, N_TWIST> TWIST_MOVE;
    };

}

#endif // CUBIE_CUBE222_HPP
