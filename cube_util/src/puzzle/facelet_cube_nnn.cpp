// Copyright 2019 Yunqi Ouyang
#include "cube_util/puzzle/facelet_cube_nnn.hpp"

#include <iostream>

#include "cube_util/utils.hpp"

namespace cube_util {

using std::to_string;
using std::invalid_argument;
using std::ostream;
using std::endl;

using cube_util::constants::kMaxSize;
using cube_util::constants::kMovePerAxis;
using cube_util::constants::kMovePerShift;
using cube_util::constants::kNAxis;
using cube_util::constants::kNFace;

using cube_util::utils::cycle4;

using cube_util::enums::Colors::U;
using cube_util::enums::Colors::R;
using cube_util::enums::Colors::F;
using cube_util::enums::Colors::D;
using cube_util::enums::Colors::L;
using cube_util::enums::Colors::B;

FaceletCubeNNN::FaceletCubeNNN(uint16_t size) {
  if (size < 2 || size > kMaxSize) {
    throw invalid_argument("The size should between 2 and " +
        to_string(kMaxSize));
  }
  size_ = size;
  facelets_ = vector<uint16_t>(kNFace * size * size);
  reset();
}

FaceletCubeNNN::FaceletCubeNNN(uint16_t size,
                               const vector<uint16_t> &facelets) {
  if (size < 2 || size > kMaxSize) {
    throw invalid_argument("The size should between 2 and " +
        to_string(kMaxSize));
  }
  if (facelets.size() != kNFace * size * size) {
    throw invalid_argument("The facelets definition length should be " +
        to_string(kNFace * size * size));
  }
  size_ = size;
  facelets_ = facelets;
}

uint16_t FaceletCubeNNN::getSize() const {
  return size_;
}

vector<uint16_t> FaceletCubeNNN::getFacelets() const {
  return facelets_;
}

string FaceletCubeNNN::prettify() const {
  using constants::kFaceNames;

  string ret;
  for (auto i = 0; i < size_; i++) {
    for (auto j = 0; j < size_ + 1; j++) {
      ret.append(" ");
    }
    for (auto j = 0; j < size_; j++) {
      ret.append(&kFaceNames[facelets_[U * size_ * size_ + i * size_ + j]], 1);
    }
    ret.append("\n");
  }
  ret.append("\n");
  for (auto i = 0; i < size_; i++) {
    for (auto j = 0; j < size_; j++) {
      ret.append(&kFaceNames[facelets_[L * size_ * size_ + i * size_ + j]], 1);
    }
    ret.append(" ");
    for (auto j = 0; j < size_; j++) {
      ret.append(&kFaceNames[facelets_[F * size_ * size_ + i * size_ + j]], 1);
    }
    ret.append(" ");
    for (auto j = 0; j < size_; j++) {
      ret.append(&kFaceNames[facelets_[R * size_ * size_ + i * size_ + j]], 1);
    }
    ret.append(" ");
    for (auto j = 0; j < size_; j++) {
      ret.append(&kFaceNames[facelets_[B * size_ * size_ + i * size_ + j]], 1);
    }
    ret.append("\n");
  }
  ret.append("\n");
  for (auto i = 0; i < size_; i++) {
    for (auto j = 0; j < size_ + 1; j++) {
      ret.append(" ");
    }
    for (auto j = 0; j < size_; j++) {
      ret.append(&kFaceNames[facelets_[D * size_ * size_ + i * size_ + j]], 1);
    }
    ret.append("\n");
  }
  return ret;
}

void FaceletCubeNNN::moveu(int layer, int amount) {
  if (layer < 1 || layer > size_) {
    throw invalid_argument("Layer must between 1 and " + to_string(size_));
  }
  if (amount < 1) {
    throw invalid_argument("Amount must be positive");
  }
  amount = amount & 3;
  for (auto c = 0; c < amount; c++) {
    if (layer == 1) {
      for (int i = 0; i < size_ / 2; i ++) {
        for (int j = i; j < size_ - i - 1; j++) {
          cycle4(
              &facelets_,
              U * size_ * size_ + (i * size_) + j,
              U * size_ * size_ + (j * size_) + (size_ - i - 1),
              U * size_ * size_ + ((size_ - i - 1) * size_) + (size_ - j - 1),
              U * size_ * size_ + ((size_ - j - 1) * size_) + i);
        }
      }
    }
    for (int i = 0; i < size_; i++) {
      cycle4(&facelets_,
             F * size_ * size_ + (layer - 1) * size_ + i,
             L * size_ * size_ + (layer - 1) * size_ + i,
             B * size_ * size_ + (layer - 1) * size_ + i,
             R * size_ * size_ + (layer - 1) * size_ + i);
    }

    if (layer == size_) {
      for (int i = 0; i < size_ / 2; i ++) {
        for (int j = i; j < size_ - i - 1; j++) {
          cycle4(
              &facelets_,
              D * size_ * size_ + (i * size_) + j,
              D * size_ * size_ + ((size_ - j - 1) * size_) + i,
              D * size_ * size_ + ((size_ - i - 1) * size_) + (size_ - j - 1),
              D * size_ * size_ + (j * size_) + (size_ - i - 1));
        }
      }
    }
  }
}

void FaceletCubeNNN::moved(int layer, int amount) {
  moveu(size_ - layer + 1, 4 - (amount & 3));
}

void FaceletCubeNNN::mover(int layer, int amount) {
  if (layer < 1 || layer > size_) {
    throw invalid_argument("Layer must between 1 and " + to_string(size_));
  }
  if (amount < 1) {
    throw invalid_argument("Amount must be positive");
  }
  amount = amount & 3;
  for (auto c = 0; c < amount; c++) {
    if (layer == 1) {
      for (int i = 0; i < size_ / 2; i ++) {
        for (int j = i; j < size_ - i - 1; j++) {
          cycle4(
              &facelets_,
              R * size_ * size_ + (i * size_) + j,
              R * size_ * size_ + (j * size_) + (size_ - i - 1),
              R * size_ * size_ + ((size_ - i - 1) * size_) + (size_ - j - 1),
              R * size_ * size_ + ((size_ - j - 1) * size_) + i);
        }
      }
    }
    for (int i = 0; i < size_; i++) {
      cycle4(&facelets_,
             U * size_ * size_ + i * size_ + (size_ - layer),
             B * size_ * size_ + (size_ - i - 1) * size_ + (layer - 1),
             D * size_ * size_ + i * size_ + (size_ - layer),
             F * size_ * size_ + i * size_ + (size_ - layer));
    }

    if (layer == size_) {
      for (int i = 0; i < size_ / 2; i ++) {
        for (int j = i; j < size_ - i - 1; j++) {
          cycle4(
              &facelets_,
              L * size_ * size_ + (i * size_) + j,
              L * size_ * size_ + ((size_ - j - 1) * size_) + i,
              L * size_ * size_ + ((size_ - i - 1) * size_) + (size_ - j - 1),
              L * size_ * size_ + (j * size_) + (size_ - i - 1));
        }
      }
    }
  }
}

void FaceletCubeNNN::movel(int layer, int amount) {
  mover(size_ - layer + 1, 4 - (amount & 3));
}

void FaceletCubeNNN::movef(int layer, int amount) {
  if (layer < 1 || layer > size_) {
    throw invalid_argument("Layer must between 1 and " + to_string(size_));
  }
  if (amount < 1) {
    throw invalid_argument("Amount must be positive");
  }
  amount = amount & 3;
  for (auto c = 0; c < amount; c++) {
    if (layer == 1) {
      for (int i = 0; i < size_ / 2; i ++) {
        for (int j = i; j < size_ - i - 1; j++) {
          cycle4(
              &facelets_,
              F * size_ * size_ + (i * size_) + j,
              F * size_ * size_ + (j * size_) + (size_ - i - 1),
              F * size_ * size_ + ((size_ - i - 1) * size_) + (size_ - j - 1),
              F * size_ * size_ + ((size_ - j - 1) * size_) + i);
        }
      }
    }
    for (int i = 0; i < size_; i++) {
      cycle4(&facelets_,
             U * size_ * size_ + (size_ - layer) * size_ + i,
             R * size_ * size_ + i * size_ + (layer - 1),
             D * size_ * size_ + (layer - 1) * size_ + (size_ - i - 1),
             L * size_ * size_ + (size_ - i - 1) * size_ + (size_ - layer));
    }

    if (layer == size_) {
      for (int i = 0; i < size_ / 2; i ++) {
        for (int j = i; j < size_ - i - 1; j++) {
          cycle4(
              &facelets_,
              B * size_ * size_ + (i * size_) + j,
              B * size_ * size_ + ((size_ - j - 1) * size_) + i,
              B * size_ * size_ + ((size_ - i - 1) * size_) + (size_ - j - 1),
              B * size_ * size_ + (j * size_) + (size_ - i - 1));
        }
      }
    }
  }
}

void FaceletCubeNNN::moveb(int layer, int amount) {
  movef(size_ - layer + 1, 4 - (amount & 3));
}

void FaceletCubeNNN::moveU(int amount) {
  moveu(1, amount);
}

void FaceletCubeNNN::moveR(int amount) {
  mover(1, amount);
}

void FaceletCubeNNN::moveF(int amount) {
  movef(1, amount);
}

void FaceletCubeNNN::moveD(int amount) {
  moved(1, amount);
}

void FaceletCubeNNN::moveL(int amount) {
  movel(1, amount);
}

void FaceletCubeNNN::moveB(int amount) {
  moveb(1, amount);
}

void FaceletCubeNNN::moveU() {
  moveU(1);
}

void FaceletCubeNNN::moveR() {
  moveR(1);
}

void FaceletCubeNNN::moveF() {
  moveF(1);
}

void FaceletCubeNNN::moveD() {
  moveD(1);
}

void FaceletCubeNNN::moveL() {
  moveL(1);
}

void FaceletCubeNNN::moveB() {
  moveB(1);
}

void FaceletCubeNNN::moveUw(int shift, int amount) {
  if (shift > size_) {
    shift = size_;
  }
  if (shift < 2) {
    shift = 2;
  }
  for (auto l = 1; l <= shift; l++) {
    moveu(l, amount);
  }
}

void FaceletCubeNNN::moveRw(int shift, int amount) {
  if (shift > size_) {
    shift = size_;
  }
  if (shift < 2) {
    shift = 2;
  }
  for (auto l = 1; l <= shift; l++) {
    mover(l, amount);
  }
}

void FaceletCubeNNN::moveFw(int shift, int amount) {
  if (shift > size_) {
    shift = size_;
  }
  if (shift < 2) {
    shift = 2;
  }
  for (auto l = 1; l <= shift; l++) {
    movef(l, amount);
  }
}

void FaceletCubeNNN::moveDw(int shift, int amount) {
  if (shift > size_) {
    shift = size_;
  }
  if (shift < 2) {
    shift = 2;
  }
  for (auto l = 1; l <= shift; l++) {
    moved(l, amount);
  }
}

void FaceletCubeNNN::moveLw(int shift, int amount) {
  if (shift > size_) {
    shift = size_;
  }
  if (shift < 2) {
    shift = 2;
  }
  for (auto l = 1; l <= shift; l++) {
    movel(l, amount);
  }
}

void FaceletCubeNNN::moveBw(int shift, int amount) {
  if (shift > size_) {
    shift = size_;
  }
  if (shift < 2) {
    shift = 2;
  }
  for (auto l = 1; l <= shift; l++) {
    moveb(l, amount);
  }
}

void FaceletCubeNNN::moveUw(int amount) {
  moveUw(2, amount);
}

void FaceletCubeNNN::moveRw(int amount) {
  moveRw(2, amount);
}

void FaceletCubeNNN::moveFw(int amount) {
  moveFw(2, amount);
}

void FaceletCubeNNN::moveDw(int amount) {
  moveDw(2, amount);
}

void FaceletCubeNNN::moveLw(int amount) {
  moveLw(2, amount);
}

void FaceletCubeNNN::moveBw(int amount) {
  moveBw(2, amount);
}

void FaceletCubeNNN::move(uint16_t move) {
  auto axis = (move / kMovePerAxis) % kNAxis;
  auto shift = move / kMovePerShift + 1;
  auto amount = move % kMovePerAxis + 1;
  if (shift > 1) {
    switch (axis) {
      case U:
        moveUw(shift, amount);
        break;
      case R:
        moveRw(shift, amount);
        break;
      case F:
        moveFw(shift, amount);
        break;
      case D:
        moveDw(shift, amount);
        break;
      case L:
        moveLw(shift, amount);
        break;
      case B:
        moveBw(shift, amount);
        break;
    }
  } else {
    switch (axis) {
      case U:
        moveU(amount);
        break;
      case R:
        moveR(amount);
        break;
      case F:
        moveF(amount);
        break;
      case D:
        moveD(amount);
        break;
      case L:
        moveL(amount);
        break;
      case B:
        moveB(amount);
        break;
    }
  }
}

void FaceletCubeNNN::reset() {
  for (auto i = 0; i < kNFace; i++) {
    fill_n(facelets_.begin() + i * size_ * size_, size_ * size_, i);
  }
}

bool FaceletCubeNNN::isSolvableIn(uint16_t max_length) const {
  if (max_length > 2) {
    throw invalid_argument("Max check length is 2");
  }
  auto ifcn = FaceletCubeNNN(size_);
  if (*this == ifcn) {
    return true;
  }
  if (max_length > 0) {
    const uint16_t kNMove = (size_ - 1) * 9;
    for (auto m = 0; m < kNMove; m++) {
      auto another = FaceletCubeNNN(size_, facelets_);
      another.move(m);
      if (another.isSolvableIn(max_length - 1)) {
        return true;
      }
    }
  }
  return false;
}

bool FaceletCubeNNN::operator==(const FaceletCubeNNN &that) const {
  return size_ == that.size_ && facelets_ == that.facelets_;
}

ostream& operator<<(ostream &os, const FaceletCubeNNN &fc) {
  return os << "FaceletCubeNNN(" << fc.size_ << ")" << endl << fc.prettify();
}

}  // namespace cube_util
