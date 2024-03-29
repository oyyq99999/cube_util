// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_222_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_222_HPP_
#include <string>

#include "cube_util/puzzle/cubie_cube_nnn.hpp"

namespace cube_util {

using std::array;

using cube222::kNMove;
using cube222::kNPerm;
using cube222::kNTwist;

////////////////////////////////////////////////////////////////////////////////
/// A class representing a 2x2x2 cube model by cubie level.
/// It declares corner permutations in this order: `URF`, `UFL`, `ULB`, `UBR`,
/// `DLF`, `DFR`, `DRB`, `DBL`. <br>
/// It declares corner orientations in the same order with these numbers:
/// - 0 means **oriented**;
/// - 1 means **clockwise** twisted once from the **oriented** status;
/// - 2 means **counter-clockwise** twisted.
///
/// Currently the last corner (cp[7] needs to be the `DBL` corner) and the
/// twist of it needs to be `0` (oriented).
////////////////////////////////////////////////////////////////////////////////
class CubieCube222 : public CubieCubeNNN {
 public:
  CubieCube222() = default;

  /**
   * Constructor of the class.
   * @param perm permutations to initialize with
   * @param twist orientations to initialize with
   */
  CubieCube222(const array<uint16_t, kNCorner> &perm,
               const array<uint16_t, kNCorner> &twist);

  /**
   * Constructor of the class.
   * @param perm permutation index to initialize with
   * @param twist orientation index to initialize with
   */
  CubieCube222(uint16_t perm, uint16_t twist);

  /**
   * Constructor of the class.
   * `index` = `perm` * `kNTwist` + `twist`
   * @param index index to initialize with
   */
  explicit CubieCube222(uint32_t index);

  void move(uint16_t move) override;  // NOLINT(build/include_what_you_use)

  uint16_t getCPIndex() const override;

  uint16_t getCOIndex() const override;

  string toString() const override;

  FaceletCubeNNN toFaceletCube() const override;

  /**
   * Create a CubieCube222 based on a FaceletCubeNNN.
   * @param fc a FaceletCubeNNN with a size of 2
   * @returns a CubieCube222 instance
   */
  static CubieCube222 fromFaceletCube(const FaceletCubeNNN &fc);

  /**
   * Get a cube in random position.
   * @returns a CubieCube222 with random state
   */
  static CubieCube222 randomCube();

  /**
   * Get a new CubieCube222 model with specified move applied to
   * an identity cube. This is used to calculate new cube states.
   * @param move the move applied
   * @returns the move cube
   */
  static const CubieCube222& getMoveCube(uint16_t move);

  /**
   * Get new permutation coordinate by applying a move to
   * specified permutation coordinate.
   * @param perm the original permutation coordinate
   * @param move the move to apply
   * @returns new permutation coordinate
   */
  static uint16_t getPermMove(uint16_t perm, uint16_t move);

  /**
   * Get new orientation coordinate by applying a move to
   * specified orientation coordinate.
   * @param twist the original orientation coordinate
   * @param move the move to apply
   * @returns new orientation coordinate
   */
  static uint16_t getTwistMove(uint16_t twist, uint16_t move);

  /**
   * Check if `this` is identical to `that`.
   * @param that another CubieCube222
   * @returns true if `this` is identical to `that`, false otherwise
   */
  bool operator==(const CubieCube222 &that) const;

 private:
  void setCP(uint16_t index) override;

  void setCO(uint16_t index) override;

  /**
   * Calculate product (_one_ * _another_) of two cubes.
   * @param[in] one the first cube
   * @param[in] another the second cube
   * @param[out] result pointer to a cube to return the result to
   */
  static void cubeMult(const CubieCube222 &one, const CubieCube222 &another,
                       CubieCube222 *result);
};

}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_CUBIE_CUBE_222_HPP_
