// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_FACELET_CUBE_NNN_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_FACELET_CUBE_NNN_HPP_
#include <cstdint>

#include <string>
#include <vector>

namespace cube_util {

using std::string;
using std::vector;

////////////////////////////////////////////////////////////////////////////////
/// A class representing a NxNxN cube model by facelet level.
/// It declares facelets in this order:
/// - Face order: URFDLB;
/// - Order in face: starting from top-left sticker, and couting rows from
///   top to bottom, and couting stickers from left to right in each row;
/// - Back side is viewed via a y2 rotation in this definition.
////////////////////////////////////////////////////////////////////////////////
class FaceletCubeNNN {
  /// Size of the cube.
  /// Currently supports from 2 to #constants::kMaxSize.
  uint16_t size_;
  /** Facelets definitions of the cube. */
  vector<uint16_t> facelets_;

  /**
   * Outputs info about the cube, includes size and facelets.
   */
  friend std::ostream& operator<<(std::ostream& os, const FaceletCubeNNN &fc);

 public:
  /**
   * Constructor of the class.
   * @param size size of the cube, currently supports
   * from 2 to #constants::kMaxSize
   */
  explicit FaceletCubeNNN(uint16_t size);

  /**
   * Constructor of the class.
   * @param size size of the cube, currently supports
   * from 2 to #constants::kMaxSize
   * @param facelets definition of the current facelets state
   */
  FaceletCubeNNN(uint16_t size, const vector<uint16_t> &facelets);

  /**
   * Get the size of the cube.
   * @returns size of the cube
   */
  uint16_t getSize() const;

  /**
   * Get current facelets status.
   * @returns a copy of #facelets_
   */
  vector<uint16_t> getFacelets() const;

  /**
   * Get a prettified string representation of the current cube state.
   * @returns prettified cube state string
   */
  string prettify() const;

  /**
   * Turn the _layer-th_ layer from U axis clokwise for _amount_ times.
   * @param layer which layer to turn, counting from 1
   * @param amount how many times to turn
   */
  void moveu(int layer, int amount);
  /**
   * Turn the _layer-th_ layer from R axis clokwise for _amount_ times.
   * @param layer which layer to turn, counting from 1
   * @param amount how many times to turn
   */
  void mover(int layer, int amount);
  /**
   * Turn the _layer-th_ layer from F axis clokwise for _amount_ times.
   * @param layer which layer to turn, counting from 1
   * @param amount how many times to turn
   */
  void movef(int layer, int amount);
  /**
   * Turn the _layer-th_ layer from D axis clokwise for _amount_ times.
   * @param layer which layer to turn, counting from 1
   * @param amount how many times to turn
   */
  void moved(int layer, int amount);
  /**
   * Turn the _layer-th_ layer from L axis clokwise for _amount_ times.
   * @param layer which layer to turn, counting from 1
   * @param amount how many times to turn
   */
  void movel(int layer, int amount);
  /**
   * Turn the _layer-th_ layer from B axis clokwise for _amount_ times.
   * @param layer which layer to turn, counting from 1
   * @param amount how many times to turn
   */
  void moveb(int layer, int amount);

  /**
   * Turn the outer U layer clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveU(int amount);
  /**
   * Turn the outer R layer clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveR(int amount);
  /**
   * Turn the outer F layer clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveF(int amount);
  /**
   * Turn the outer D layer clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveD(int amount);
  /**
   * Turn the outer L layer clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveL(int amount);
  /**
   * Turn the outer B layer clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveB(int amount);

  /**
   * Turn the outer U layer clokwise once.
   */
  void moveU();
  /**
   * Turn the outer R layer clokwise once.
   */
  void moveR();
  /**
   * Turn the outer F layer clokwise once.
   */
  void moveF();
  /**
   * Turn the outer D layer clokwise once.
   */
  void moveD();
  /**
   * Turn the outer L layer clokwise once.
   */
  void moveL();
  /**
   * Turn the outer B layer clokwise once.
   */
  void moveB();

  /**
   * Turn the outer _shift_ layers from U axis clokwise for _amount_ times.
   * @param shift how many layers to turn, this ranges from _2_ to #size_
   * @param amount how many times to turn
   */
  void moveUw(int shift, int amount);
  /**
   * Turn the outer _shift_ layers from R axis clokwise for _amount_ times.
   * @param shift how many layers to turn, this ranges from _2_ to #size_
   * @param amount how many times to turn
   */
  void moveRw(int shift, int amount);
  /**
   * Turn the outer _shift_ layers from F axis clokwise for _amount_ times.
   * @param shift how many layers to turn, this ranges from _2_ to #size_
   * @param amount how many times to turn
   */
  void moveFw(int shift, int amount);
  /**
   * Turn the outer _shift_ layers from D axis clokwise for _amount_ times.
   * @param shift how many layers to turn, this ranges from _2_ to #size_
   * @param amount how many times to turn
   */
  void moveDw(int shift, int amount);
  /**
   * Turn the outer _shift_ layers from L axis clokwise for _amount_ times.
   * @param shift how many layers to turn, this ranges from _2_ to #size_
   * @param amount how many times to turn
   */
  void moveLw(int shift, int amount);
  /**
   * Turn the outer _shift_ layers from B axis clokwise for _amount_ times.
   * @param shift how many layers to turn, this ranges from _2_ to #size_
   * @param amount how many times to turn
   */
  void moveBw(int shift, int amount);

  /**
   * Turn the outer **2 layers** from U axis clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveUw(int amount);
  /**
   * Turn the outer **2 layers** from R axis clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveRw(int amount);
  /**
   * Turn the outer **2 layers** from F axis clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveFw(int amount);
  /**
   * Turn the outer **2 layers** from D axis clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveDw(int amount);
  /**
   * Turn the outer **2 layers** from L axis clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveLw(int amount);
  /**
   * Turn the outer **2 layers** from B axis clokwise for _amount_ times.
   * @param amount how many times to turn
   */
  void moveBw(int amount);

  /**
   * Apply move to the cube.
   * @param move move to apply
   */
  void move(uint16_t move);  // NOLINT(build/include_what_you_use)

  /**
   * Reset the cube to solved state.
   */
  void reset();

  /**
   * Check whether the cube is solvable within given length.
   * @param max_length max length to attempt
   * @returns whether the cube is solvable within given length
   */
  bool isSolvableIn(uint16_t max_length) const;

  /**
   * Check if `this` is identical to `that`.
   * @param that another FaceCubeNNN
   * @returns true if `this` is identical to `that`, false otherwise
   */
  bool operator==(const FaceletCubeNNN &that) const;
};

}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_PUZZLE_FACELET_CUBE_NNN_HPP_
