// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_333_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_333_HPP_
#include <string>

#include "cube_util/puzzle/cubie_cube_nnn.hpp"

namespace cube_util {

using cube333::kNEdge;
using cube333::kNMove;

////////////////////////////////////////////////////////////////////////////////
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
/// It declares edge orientations in the same order with 0 means **oriented**
/// and 1 means **flipped**. By `oriented`, it means the state can be solved
/// with <U, D, L, R, F2, B2> moves.
////////////////////////////////////////////////////////////////////////////////
class CubieCube333 : public CubieCubeNNN {
  /** Permutations of the edges. */
  array<uint16_t, kNEdge> ep_;

  /** Orientations of the edges. */
  array<uint16_t, kNEdge> eo_;

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
   * Set first 8 edge permutation state according to given index.
   * @param index specified index
   */
  void setUD8EP(uint16_t index);

  /**
   * Set E-slice edge permutation state according to given index.
   * @param index specified index
   */
  void setSliceEP(uint16_t index);

  /**
   * Set E-slice edges positions according to given index.
   */
  void setSlicePosition(uint16_t index);

  /**
   * Calculate product (_one_ * _another_) of two cubes.
   * @param[in] one the first cube
   * @param[in] another the second cube
   * @param[out] result pointer to a cube to return the result to
   */
  static void cubeMult(const CubieCube333 &one, const CubieCube333 &another,
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
  CubieCube333(const array<uint16_t, kNCorner> &cp,
               const array<uint16_t, kNCorner> &co,
               const array<uint16_t, kNEdge> &ep,
               const array<uint16_t, kNEdge> &eo);

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

  /**
   * Calculate first 8 edge permutation index of current state.
   */
  uint16_t getUD8EPIndex() const;

  /**
   * Calculate E-slice edges positions combination index of current state.
   */
  uint16_t getSlicePositionIndex() const;

  /**
   * Calculate E-slice edges positions index of current state.
   */
  uint16_t getSliceEPIndex() const;

  string toString() const override;

  FaceletCubeNNN toFaceletCube() const override;

  /**
   * Create a CubieCube333 based on a FaceletCubeNNN.
   * @param fc a FaceletCubeNNN with a size of 3
   * @returns a CubieCube333 instance
   */
  static CubieCube333 fromFaceletCube(const FaceletCubeNNN &fc);

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
   * Get a cube with phase1 solved in random position.
   * @returns a random CubieCube333 with phase1 solved
   */
  static CubieCube333 randomDRCube();

  /**
   * Get a new CubieCube333 model with specified move applied to
   * an identity cube. This is used to calculate new cube states.
   * @param move the move applied
   * @returns the move cube
   */
  static const CubieCube333& getMoveCube(uint16_t move);

  /**
   * Get new twist coordinate by applying a move to specified twist coordinate.
   * @param twist the original twist coordinate
   * @param move the move to apply
   * @returns new twist coordinate
   */
  static uint16_t getTwistMove(uint16_t twist, uint16_t move);

  /**
   * Get new flip coordinate by applying a move to specified flip coordinate.
   * @param flip the original flip coordinate
   * @param move the move to apply
   * @returns new flip coordinate
   */
  static uint16_t getFlipMove(uint16_t flip, uint16_t move);

  /**
   * Get new E-slice edges positions coordinate by applying a move to
   * specified original coordinate.
   * @param slicePositionIndex the original E-slice edges positions coordinate
   * @param move the move to apply
   * @returns new E-slice edges positions coordinate
   */
  static uint16_t getSlicePositionMove(uint16_t slicePositionIndex,
                                       uint16_t move);

  /**
   * Get new UD 8 edges positions coordinate by applying a move to
   * specified original coordinate.
   * @param ud8EP the original UD 8 edges positions coordinate
   * @param index the index of phase2 move to apply
   * @returns new UD 8 edges positions coordinate
   */
  static uint16_t getUD8EPMove(uint16_t ud8EP, uint16_t index);

  /**
   * Get new corner permutation coordinate by applying a move to
   * specified corner permutation coordinate.
   * @param cp the original corner permutation coordinate
   * @param index the index of phase2 move to apply
   * @returns new corner permutation coordinate
   */
  static uint16_t getCPMove(uint16_t cp, uint16_t index);

  /**
   * Get new slice edge permutation coordinate by applying a move to
   * specified slice edge permutation coordinate.
   * @param sliceEP the original slice edge permutation coordinate
   * @param index the index of phase2 move to apply
   * @returns new slice edge permutation coordinate
   */
  static uint16_t getSliceEPMove(uint16_t sliceEP, uint16_t index);

  /**
   * Check if `this` is identical to `that`.
   * @param that another CubieCube333
   * @returns true if `this` is identical to `that`, false otherwise
   */
  bool operator==(const CubieCube333 &that) const;
};
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_333_HPP_
