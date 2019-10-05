// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBENNN_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBENNN_HPP_
#include<iostream>
#include<array>
#include<string>
#include<cube_util/FaceletCubeNNN.hpp>
#include<cube_util/Utils.hpp>

namespace cube_util {

    using std::array;
    using std::ostream;

    using constants::N_CORNER;

////////////////////////////////////////////////////////////////////////////
/// An abstract class representing common part of any NxNxN cube models by
/// cubie level.
/// It declares corner permutations in this order: `URF`, `UFL`, `ULB`,
/// `UBR`, `DLF`, `DFR`, `DRB`, `DBL`. <br>
/// It declares corner orientations in the same order with these numbers:
/// - 0 means **oriented**;
/// - 1 means **clockwise** twisted once from the **oriented** status;
/// - 2 means **counter-clockwise** twisted.
////////////////////////////////////////////////////////////////////////////
class CubieCubeNNN {
    /**
     * Outputs info about the cube, includes perms and twists
     */
    friend ostream& operator<<(ostream& os, const CubieCubeNNN &cc);

 protected:
    /** Permutations of the corners. */
    array<uint16_t, N_CORNER> cp;

    /** Orientations of the corners. */
    array<uint16_t, N_CORNER> co;

    /**
     * Set corner permutation state according to given index.
     * @param index specified index
     */
    virtual void setCP(uint16_t index);

    /**
     * Set corner orientation state according to given index.
     * @param index specified index
     */
    virtual void setCO(uint16_t index);

 public:
    CubieCubeNNN();

    /**
     * Apply move to the current cube.
     * @param move the move to apply, using move from cube_util::enums::Moves
     */
    virtual void move(uint16_t move) = 0;  // NOLINT(build/include_what_you_use)

    /**
     * Calculate corner permutation index of current state.
     */
    virtual uint16_t getCPIndex() const;

    /**
     * Calculate corner orientation index of current state.
     */
    virtual uint16_t getCOIndex() const;

    /**
     * Get a string representation of the cube state.
     * @returns a string describing the current state.
     */
    virtual string toString() const = 0;

    /**
     * Create a FaceletCubeNNN based on the CubieCubeNNN.
     * @returns a FaceletCubeNNN instance
     */
    virtual FaceletCubeNNN toFaceletCube() = 0;

    virtual ~CubieCubeNNN() = default;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBIECUBENNN_HPP_
