#ifndef CUBE222SOLVER_HPP
#define CUBE222SOLVER_HPP
#include<cube_util/CubieCube222.hpp>

namespace cube_util {


    ////////////////////////////////////////////////////////////////////////////
    /// A 2x2x2 cube solver utilizing the IDA* algorithm with prunning tables.
    ////////////////////////////////////////////////////////////////////////////
    class Cube222Solver {

        /** The cube to solve */
        CubieCube222 cc;
        /** Array storing solution move sequences */
        array<uint16_t, 11> solution;
        /** Length of the solution */
        int16_t solutionLength = -1;

        bool search(uint64_t perm, uint16_t twist, uint16_t moveCount,
            int16_t lastAxis, uint16_t depth, bool saveSolution);
        void _solve(uint16_t minLength);

    public:

        Cube222Solver() = default;

        /**
         * Constructor of the class.
         * @param c the cube to solve
         */
        Cube222Solver(CubieCube222 c);

        /**
         * Get the solution length.
         * @returns length of the current solution or -1 if not solved (yet)
         */
        int16_t getSolutionLength() const;

        /**
         * Get solution sequence for the cube.
         * @returns sequence to solve the cube
         */
        string solve();

        /**
         * Get solution sequence of at least `minLength` moves for the cube.
         * @param minLength minimal length of the solution
         * @returns sequence to solve the cube
         */
        string solve(uint16_t minLength);

        /**
         * Get generator sequence for the cube.
         * @returns sequence to generate the cube state
         */
        string generate();

        /**
         * Get generator sequence of at least `minLength` moves for the cube.
         * @param minLength minimal length of the generator
         * @returns sequence to generate the cube state
         */
        string generate(uint16_t minLength);


        /**
         * Check whether the cube is solvable within given length.
         * @param maxLength maxLength to attempt
         * @returns whether the cube is solvable within given length
         */
        bool isSolvableIn(uint16_t maxLength);

        /**
         * Pruning table for 2x2x2 permutations.
         */
        static const array<uint16_t, ((N_PERM + 3) >> 2)> PERM_PRUNING;

        /**
         * Pruning table for 2x2x2 orientations.
         */
        static const array<uint16_t, ((N_TWIST + 3) >> 2)> TWIST_PRUNING;

    };

}

#endif // CUBE222SOLVER_HPP
