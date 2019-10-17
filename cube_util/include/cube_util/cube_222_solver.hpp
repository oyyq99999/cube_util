// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE_222_SOLVER_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE_222_SOLVER_HPP_
#include <memory>

#include "cube_util/puzzle/cubie_cube_222.hpp"
#include "cube_util/move_sequence.hpp"

namespace cube_util {

using std::unique_ptr;

using cube222::kMaxLength;

////////////////////////////////////////////////////////////////////////////////
/// A 2x2x2 cube solver utilizing the IDA* algorithm with prunning tables.
////////////////////////////////////////////////////////////////////////////////
class Cube222Solver {
  /** The cube to solve */
  CubieCube222 cc_;

  /** Array storing solution move sequences */
  array<uint16_t, kMaxLength> solution_;

  /** Length of the solution */
  int16_t solution_length_ = -1;

  bool search(uint16_t perm, uint16_t twist, uint16_t moveCount,
              uint16_t lastAxis, uint16_t depth, bool saveSolution);

  void _solve(uint16_t minLength);

 public:
  Cube222Solver() = default;

  /**
   * Constructor of the class.
   * @param c the cube to solve
   */
  explicit Cube222Solver(const CubieCube222 &c);

  /**
   * Get the solution length.
   * @returns length of the current solution or -1 if not solved (yet)
   */
  int16_t getSolutionLength() const;

  /**
   * Get solution sequence of at least `minLength` moves for the cube.
   * @param minLength minimal length of the solution
   * @returns a pointer to sequence to solve the cube
   */
  unique_ptr<MoveSequence> solve(uint16_t minLength = 0);

  /**
   * Get generator sequence of at least `minLength` moves for the cube.
   * @param minLength minimal length of the generator
   * @returns a pointer to sequence to generate the cube state
   */
  unique_ptr<MoveSequence> generate(uint16_t minLength = 0);

  /**
   * Check whether the cube is solvable within given length.
   * @param max_length max length to attempt
   * @returns whether the cube is solvable within given length
   */
  bool isSolvableIn(uint16_t max_length);

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

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_CUBE_222_SOLVER_HPP_
