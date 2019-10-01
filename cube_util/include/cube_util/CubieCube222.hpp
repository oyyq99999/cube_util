// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBE222_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBE222_HPP_
#include<string>
#include<cube_util/CubieCubeNNN.hpp>

namespace cube_util {

    using std::array;

    using cube222::N_MOVE;
    using cube222::N_PERM;
    using cube222::N_TWIST;

////////////////////////////////////////////////////////////////////////////
/// A class representing a 2x2x2 cube model by cubie level.
/// It declares corner permutations in this order: `URF`, `UFL`, `ULB`,
/// `UBR`, `DLF`, `DFR`, `DRB`, `DBL`. <br>
/// It declares corner orientations in the same order with these numbers:
/// - 0 means **oriented**;
/// - 1 means **clockwise** twisted once from the **oriented** status;
/// - 2 means **counter-clockwise** twisted.
///
/// Currently the last corner (cp[7] needs to be the `DBL` corner) and the
/// twist of it needs to be `0` (oriented).
////////////////////////////////////////////////////////////////////////////
class CubieCube222: public CubieCubeNNN {
    void setCP(uint16_t index) override;

    void setCO(uint16_t) override;

    /**
     * Calculate product (_one_ * _another_) of two cubes.
     * @param[in] one the first cube
     * @param[in] another the second cube
     * @param[out] result pointer to a cube to return the result to
     */
    static void cubeMult(CubieCube222 one, CubieCube222 another,
        CubieCube222 *result);

 public:
    CubieCube222() {}

    /**
     * Constructor of the class.
     * @param perm permutations to initialize with
     * @param twist orientations to initialize with
     */
    CubieCube222(array<uint16_t, N_CORNER> perm,
        array<uint16_t, N_CORNER> twist);

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
    explicit CubieCube222(uint32_t index);

    /**
     * Apply move to the current cube.
     * @param move the move to apply, as described in cube_util::constants
     */
    void move(int move);  // NOLINT(build/include_what_you_use)

    uint16_t getCP() const override;

    uint16_t getCO() const override;

    string toString() const override;

    FaceletCubeNNN toFaceletCube() override;

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
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBE222_HPP_
