// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE333SOLVER_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE333SOLVER_HPP_
#include<memory>
#include<cube_util/MoveSequence.hpp>
#include<cube_util/CubieCube333.hpp>

namespace cube_util {

    using std::unique_ptr;

    using cube333::N_MAX_LENGTH;

////////////////////////////////////////////////////////////////////////////
/// A 3x3x3 cube solver utilizing the two phase algorithm introduced by
/// Herbert Kociemba.
////////////////////////////////////////////////////////////////////////////
class Cube333Solver {
    /** The cube to solve */
    CubieCube333 cc;

    /** Array storing solution move sequences */
    array<uint16_t, N_MAX_LENGTH> solution;

    /** Length of the solution */
    int16_t solutionLength = -1;

    /** Length of phase 1 of the solution */
    int16_t phase1Length = -1;

    bool _solve(uint16_t maxLength);

    bool phase1(uint16_t co, uint16_t eo, uint16_t slice, uint16_t moveCount,
        uint16_t lastAxis, uint16_t depth, uint16_t maxLength, bool checkOnly);

    bool initPhase2(uint16_t lastAxis, uint16_t depth, uint16_t maxLength);

    bool phase2(uint16_t cp, uint16_t ud8EP, uint16_t sliceEP,
        uint16_t moveCount, uint16_t lastAxis, uint16_t depth);

 public:
    Cube333Solver() = default;

    /**
     * Constructor of the class.
     * @param c the cube to solve
     */
    explicit Cube333Solver(CubieCube333 c);

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
     * Get solution sequence of at most `maxLength` moves for the cube.
     * @param maxLength maximal length of the solution
     * @returns a pointer to sequence to solve the cube
     */
    unique_ptr<MoveSequence> solve(uint16_t maxLength);

    /**
     * Get generator sequence for the cube.
     * @returns a pointer to sequence to generate the cube state
     */
    unique_ptr<MoveSequence> generate();

    /**
     * Get generator sequence of at most `maxLength` moves for the cube.
     * @param maxLength maximal length of the generator
     * @returns a pointer to sequence to generate the cube state
     */
    unique_ptr<MoveSequence> generate(uint16_t maxLength);

    /**
     * Check whether the cube is solvable within given length.
     * @param maxLength maxLength to attempt
     * @returns whether the cube is solvable within given length
     */
    bool isSolvableIn(uint16_t maxLength);

    /**
     * Get pruning value for a specified twist and
     * E-slice position combination.
     * @param twist the twist index to lookup
     * @param slice the E-slice position index to lookup
     * @returns the pruning value
     */
    static uint16_t getTwistSlicePruning(uint16_t twist, uint16_t slice);

    /**
     * Get pruning value for a specified flip and
     * E-slice position combination.
     * @param flip the flip index to lookup
     * @param slice the E-slice position index to lookup
     * @returns the pruning value
     */
    static uint16_t getFlipSlicePruning(uint16_t flip, uint16_t slice);

    /**
     * Get pruning value for a specified corner permutation and
     * E-slice position combination.
     * @param cp the corner permutation index to lookup
     * @param sliceEP the E-slice permutation index to lookup
     * @returns the pruning value
     */
    static uint16_t getCPSliceEPPruning(uint16_t cp, uint16_t sliceEP);

    /**
     * Get pruning value for a specified UD 8 edge permutation and
     * E-slice position combination.
     * @param ud8EP the UD 8 edge permutation index to lookup
     * @param sliceEP the E-slice permutation index to lookup
     * @returns the pruning value
     */
    static uint16_t getUD8EPSliceEPPruning(uint16_t ud8EP, uint16_t sliceEP);
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE333SOLVER_HPP_
