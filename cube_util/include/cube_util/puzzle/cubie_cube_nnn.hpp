// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_NNN_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_NNN_HPP_
#include <array>
#include <iostream>
#include <string>

#include "cube_util/puzzle/facelet_cube_nnn.hpp"
#include "cube_util/utils.hpp"

namespace cube_util {

using std::array;
using std::ostream;

using constants::kNCorner;

////////////////////////////////////////////////////////////////////////////////
/// An abstract class representing common part of any NxNxN cube models by
/// cubie level.
/// It declares corner permutations in this order: `URF`, `UFL`, `ULB`,
/// `UBR`, `DLF`, `DFR`, `DRB`, `DBL`. <br>
/// It declares corner orientations in the same order with these numbers:
/// - 0 means **oriented**;
/// - 1 means **clockwise** twisted once from the **oriented** status;
/// - 2 means **counter-clockwise** twisted.
////////////////////////////////////////////////////////////////////////////////
class CubieCubeNNN {
  /**
   * Outputs info about the cube, includes perms and twists
   */
  friend ostream& operator<<(ostream& os, const CubieCubeNNN &cc);

 protected:
  /** Permutations of the corners. */
  array<uint16_t, kNCorner> cp_;

  /** Orientations of the corners. */
  array<uint16_t, kNCorner> co_;

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
  virtual FaceletCubeNNN toFaceletCube() const = 0;

  virtual ~CubieCubeNNN() = default;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_NNN_HPP_
