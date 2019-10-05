// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE222SOLVER_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE222SOLVER_HPP_
#include<memory>
#include<cube_util/CubieCube222.hpp>
#include<cube_util/MoveSequence.hpp>

namespace cube_util {

    using std::unique_ptr;

    using cube222::N_MAX_LENGTH;

////////////////////////////////////////////////////////////////////////////
/// A 2x2x2 cube solver utilizing the IDA* algorithm with prunning tables.
////////////////////////////////////////////////////////////////////////////
class Cube222Solver {
    /** The cube to solve */
    CubieCube222 cc;

    /** Array storing solution move sequences */
    array<uint16_t, N_MAX_LENGTH> solution;

    /** Length of the solution */
    int16_t solutionLength = -1;

    bool search(uint16_t perm, uint16_t twist, uint16_t moveCount,
        uint16_t lastAxis, uint16_t depth, bool saveSolution);

    void _solve(uint16_t minLength);

 public:
    Cube222Solver() = default;

    /**
     * Constructor of the class.
     * @param c the cube to solve
     */
    explicit Cube222Solver(CubieCube222 c);

    /**
     * Get the solution length.
     * @returns length of the current solution or -1 if not solved (yet)
     */
    int16_t getSolutionLength() const;

    /**
     * Get solution sequence for the cube.
     * @returns a pointer to sequence to solve the cube
     */
    unique_ptr<MoveSequence> solve();

    /**
     * Get solution sequence of at least `minLength` moves for the cube.
     * @param minLength minimal length of the solution
     * @returns a pointer to sequence to solve the cube
     */
    unique_ptr<MoveSequence> solve(uint16_t minLength);

    /**
     * Get generator sequence for the cube.
     * @returns a pointer to sequence to generate the cube state
     */
    unique_ptr<MoveSequence> generate();

    /**
     * Get generator sequence of at least `minLength` moves for the cube.
     * @param minLength minimal length of the generator
     * @returns a pointer to sequence to generate the cube state
     */
    unique_ptr<MoveSequence> generate(uint16_t minLength);

    /**
     * Check whether the cube is solvable within given length.
     * @param maxLength maxLength to attempt
     * @returns whether the cube is solvable within given length
     */
    bool isSolvableIn(uint16_t maxLength);

    /**
     * Get pruning value for a specified permutation.
     * @param perm the permutation index to lookup
     * @returns the pruning value
     */
    static uint16_t getPermPruning(uint16_t perm);

    /**
     * Get pruning value for a specified orientation.
     * @param twist the orientation index to lookup
     * @returns the pruning value
     */
    static uint16_t getTwistPruning(uint16_t twist);
};

}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE222SOLVER_HPP_
