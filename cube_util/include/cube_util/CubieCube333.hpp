// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBE333_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBE333_HPP_
#include<string>
#include<cube_util/CubieCubeNNN.hpp>

namespace cube_util {

    using cube333::N_EDGE;
    using cube333::N_MOVE;

////////////////////////////////////////////////////////////////////////////
/// A class representing a 3x3x3 cube model by cubie level.
/// It declares corner permutations in this order: `URF`, `UFL`, `ULB`,
/// `UBR`, `DLF`, `DFR`, `DRB`, `DBL`. <br>
/// It declares corner orientations in the same order with these numbers:
/// - 0 means **oriented**;
/// - 1 means **clockwise** twisted once from the **oriented** status;
/// - 2 means **counter-clockwise** twisted.
///
/// It declares edge permutations in this order: `UF`, `UL`, `UB`, `UR`,
/// `DF`, `DR`, `DB`, `DL`, `FL`, `BL`, `BR`, `FR`. <br>
/// It declares edge orientations in the same order with 0 means
/// **oriented** and 1 means **flipped**. By `oriented`, it means the state
/// can be solved with <U, D, L, R, F2, B2> moves.
////////////////////////////////////////////////////////////////////////////
class CubieCube333: public CubieCubeNNN {
    /** Permutations of the edges. */
    array<uint16_t, N_EDGE> ep;

    /** Orientations of the edges. */
    array<uint16_t, N_EDGE> eo;

    /**
     * Set edge permutation state according to given index.
     * @param index specified index
     */
    void setEP(uint32_t index);

    /**
     * Set edge orientation state according to given index.
     * @param index specified index
     */
    void setEO(uint16_t index);

    /**
     * Calculate product (_one_ * _another_) of two cubes.
     * @param[in] one the first cube
     * @param[in] another the second cube
     * @param[out] result pointer to a cube to return the result to
     */
    static void cubeMult(CubieCube333 one, CubieCube333 another,
        CubieCube333 *result);

 public:
    CubieCube333();

    /**
     * Constructor of the class.
     * @param cp corner permutations to initialize with
     * @param co corner orientations to initialize with
     * @param ep edge permutations to initialize with
     * @param eo edge orientations to initialize with
     */
    CubieCube333(array<uint16_t, N_CORNER> cp, array<uint16_t, N_CORNER> co,
        array<uint16_t, N_EDGE> ep, array<uint16_t, N_EDGE> eo);

    /**
     * Constructor of the class.
     * @param cp corner permutation index to initialize with
     * @param co corner orientation index to initialize with
     * @param ep edge permutation index to initialize with
     * @param eo edge orientation index to initialize with
     */
    CubieCube333(uint16_t cp, uint16_t co, uint32_t ep, uint16_t eo);

    void move(uint16_t move) override;  // NOLINT(build/include_what_you_use)

    /**
     * Calculate edge permutation index of current state.
     */
    uint32_t getEPIndex() const;

    /**
     * Calculate edge orientation index of current state.
     */
    uint16_t getEOIndex() const;

    string toString() const override;

    FaceletCubeNNN toFaceletCube() override;

    /**
     * Create a CubieCube333 based on a FaceletCubeNNN.
     * @param fc a FaceletCubeNNN with a size of 3
     * @returns a CubieCube333 instance
     */
    static CubieCube333 fromFaceletCube(FaceletCubeNNN fc);

    /**
     * Check if a permutation combination is solvable.
     * @param cpi corner permutation index
     * @param epi edge permutation index
     * @returns `true` if solvable, `false` otherwise
     */
    static bool isSolvable(uint16_t cpi, uint32_t epi);

    /**
     * Get a cube in random position.
     * @returns a CubieCube333 with random state
     */
    static CubieCube333 randomCube();

    /**
     * Get a new CubieCube333 model with specified move applied to
     * an identity cube. This is used to calculate new cube states.
     * @param move the move applied
     * @returns the move cube
     */
    static CubieCube333 getMoveCube(uint16_t move);

    /**
     * Check if `this` is identical to `that`.
     * @param that another CubieCube333
     * @returns true if `this` is identical to `that`, false otherwise
     */
    bool operator==(const CubieCube333 &that) const;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBE333_HPP_
