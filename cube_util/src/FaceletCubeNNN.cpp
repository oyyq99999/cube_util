#include<stdexcept>
#include<algorithm>
#include<string>
#include<iostream>
#include<cube_util/FaceletCubeNNN.hpp>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    using namespace constants;
    using namespace utils;
    using namespace enums;

    FaceletCubeNNN::FaceletCubeNNN(uint16_t size) {
        if (size < 2 || size > MAX_SIZE) {
            throw invalid_argument("The size should between 2 and " + to_string(MAX_SIZE));
        }
        this->size = size;
        this->facelets = vector<uint16_t>(6 * size * size);
        for (auto i = 0; i < 6; i++) {
            fill_n(this->facelets.begin() + i * size * size, size * size, i);
        }
    }

    FaceletCubeNNN::FaceletCubeNNN(uint16_t size, vector<uint16_t> facelets) {
        if (size < 2 || size > MAX_SIZE) {
            throw invalid_argument("The size should between 2 and " + to_string(MAX_SIZE));
        }
        if (facelets.size() != 6 * size * size) {
            throw invalid_argument("The facelets definition length should be " +
                to_string(6 * size * size));
        }
        this->size = size;
        this->facelets = facelets;
    }

    uint16_t FaceletCubeNNN::getSize() const {
        return this->size;
    }

    vector<uint16_t> FaceletCubeNNN::getFacelets() const {
        return this->facelets;
    }

    string FaceletCubeNNN::prettify() const {
        string ret;
        auto size = this->size;
        for (auto i = 0; i < size; i++) {
            for (auto j = 0; j < size + 1; j++) {
                ret.append(" ");
            }
            for (auto j = 0; j < size; j++) {
                ret.append(&FACE_NAMES[this->facelets[U * size * size + i * size + j]], 1);
            }
            ret.append("\n");
        }
        ret.append("\n");
        for (auto i = 0; i < size; i++) {
            for (auto j = 0; j < size; j++) {
                ret.append(&FACE_NAMES[this->facelets[L * size * size + i * size + j]], 1);
            }
            ret.append(" ");
            for (auto j = 0; j < size; j++) {
                ret.append(&FACE_NAMES[this->facelets[F * size * size + i * size + j]], 1);
            }
            ret.append(" ");
            for (auto j = 0; j < size; j++) {
                ret.append(&FACE_NAMES[this->facelets[R * size * size + i * size + j]], 1);
            }
            ret.append(" ");
            for (auto j = 0; j < size; j++) {
                ret.append(&FACE_NAMES[this->facelets[B * size * size + i * size + j]], 1);
            }
            ret.append("\n");
        }
        ret.append("\n");
        for (auto i = 0; i < size; i++) {
            for (auto j = 0; j < size + 1; j++) {
                ret.append(" ");
            }
            for (auto j = 0; j < size; j++) {
                ret.append(&FACE_NAMES[this->facelets[D * size * size + i * size + j]], 1);
            }
            ret.append("\n");
        }
        return ret;
    }

    void FaceletCubeNNN::moveu(int layer, int amount) {
        if (layer < 1 || layer > size) {
            throw invalid_argument("Layer must between 1 and " + to_string(size));
        }
        if (amount < 1) {
            throw invalid_argument("Amount must be positive");
        }
        amount = amount & 3;
        auto size = this->size;
        for (auto c = 0; c < amount; c++) {
            if (layer == 1) {
                for (int i = 0; i < size / 2; i ++) {
                    for (int j = i; j < size - i - 1; j++) {
                        cycle4(this->facelets,
                            U * size * size + (i * size) + j,
                            U * size * size + (j * size) + (size - i - 1),
                            U * size * size + ((size - i - 1) * size) + (size - j - 1),
                            U * size * size + ((size - j - 1) * size) + i
                        );
                    }
                }
            }
            for (int i = 0; i < size; i++) {
                cycle4(this->facelets,
                    F * size * size + (layer - 1) * size + i,
                    L * size * size + (layer - 1) * size + i,
                    B * size * size + (layer - 1) * size + i,
                    R * size * size + (layer - 1) * size + i
                );
            }

            if (layer == size) {
                for (int i = 0; i < size / 2; i ++) {
                    for (int j = i; j < size - i - 1; j++) {
                        cycle4(this->facelets,
                            D * size * size + (i * size) + j,
                            D * size * size + ((size - j - 1) * size) + i,
                            D * size * size + ((size - i - 1) * size) + (size - j - 1),
                            D * size * size + (j * size) + (size - i - 1)
                        );
                    }
                }
            }
        }
    }

    void FaceletCubeNNN::moved(int layer, int amount) {
        moveu(this->size - layer + 1, 4 - (amount & 3));
    }

    void FaceletCubeNNN::mover(int layer, int amount) {
        if (layer < 1 || layer > size) {
            throw invalid_argument("Layer must between 1 and " + to_string(size));
        }
        if (amount < 1) {
            throw invalid_argument("Amount must be positive");
        }
        amount = amount & 3;
        auto size = this->size;
        for (auto c = 0; c < amount; c++) {
            if (layer == 1) {
                for (int i = 0; i < size / 2; i ++) {
                    for (int j = i; j < size - i - 1; j++) {
                        cycle4(this->facelets,
                            R * size * size + (i * size) + j,
                            R * size * size + (j * size) + (size - i - 1),
                            R * size * size + ((size - i - 1) * size) + (size - j - 1),
                            R * size * size + ((size - j - 1) * size) + i
                        );
                    }
                }
            }
            for (int i = 0; i < size; i++) {
                cycle4(this->facelets,
                    U * size * size + i * size + (size - layer),
                    B * size * size + (size - i - 1) * size + (layer - 1),
                    D * size * size + i * size + (size - layer),
                    F * size * size + i * size + (size - layer)
                );
            }

            if (layer == size) {
                for (int i = 0; i < size / 2; i ++) {
                    for (int j = i; j < size - i - 1; j++) {
                        cycle4(this->facelets,
                            L * size * size + (i * size) + j,
                            L * size * size + ((size - j - 1) * size) + i,
                            L * size * size + ((size - i - 1) * size) + (size - j - 1),
                            L * size * size + (j * size) + (size - i - 1)
                        );
                    }
                }
            }
        }
    }

    void FaceletCubeNNN::movel(int layer, int amount) {
        mover(this->size - layer + 1, 4 - (amount & 3));
    }

    void FaceletCubeNNN::movef(int layer, int amount) {
        if (layer < 1 || layer > size) {
            throw invalid_argument("Layer must between 1 and " + to_string(size));
        }
        if (amount < 1) {
            throw invalid_argument("Amount must be positive");
        }
        amount = amount & 3;
        auto size = this->size;
        for (auto c = 0; c < amount; c++) {
            if (layer == 1) {
                for (int i = 0; i < size / 2; i ++) {
                    for (int j = i; j < size - i - 1; j++) {
                        cycle4(this->facelets,
                            F * size * size + (i * size) + j,
                            F * size * size + (j * size) + (size - i - 1),
                            F * size * size + ((size - i - 1) * size) + (size - j - 1),
                            F * size * size + ((size - j - 1) * size) + i
                        );
                    }
                }
            }
            for (int i = 0; i < size; i++) {
                cycle4(this->facelets,
                    U * size * size + (size - layer) * size + i,
                    R * size * size + i * size + (layer - 1),
                    D * size * size + (layer - 1) * size + (size - i - 1),
                    L * size * size + (size - i - 1) * size + (size - layer)
                );
            }

            if (layer == size) {
                for (int i = 0; i < size / 2; i ++) {
                    for (int j = i; j < size - i - 1; j++) {
                        cycle4(this->facelets,
                            B * size * size + (i * size) + j,
                            B * size * size + ((size - j - 1) * size) + i,
                            B * size * size + ((size - i - 1) * size) + (size - j - 1),
                            B * size * size + (j * size) + (size - i - 1)
                        );
                    }
                }
            }
        }
    }

    void FaceletCubeNNN::moveb(int layer, int amount) {
        movef(this->size - layer + 1, 4 - (amount & 3));
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
        if (shift > this->size) {
            shift = this->size;
        }
        if (shift < 2) {
            shift = 2;
        }
        for (auto l = 1; l <= shift; l++) {
            moveu(l, amount);
        }
    }

    void FaceletCubeNNN::moveRw(int shift, int amount) {
        if (shift > this->size) {
            shift = this->size;
        }
        if (shift < 2) {
            shift = 2;
        }
        for (auto l = 1; l <= shift; l++) {
            mover(l, amount);
        }
    }

    void FaceletCubeNNN::moveFw(int shift, int amount) {
        if (shift > this->size) {
            shift = this->size;
        }
        if (shift < 2) {
            shift = 2;
        }
        for (auto l = 1; l <= shift; l++) {
            movef(l, amount);
        }
    }

    void FaceletCubeNNN::moveDw(int shift, int amount) {
        if (shift > this->size) {
            shift = this->size;
        }
        if (shift < 2) {
            shift = 2;
        }
        for (auto l = 1; l <= shift; l++) {
            moved(l, amount);
        }
    }

    void FaceletCubeNNN::moveLw(int shift, int amount) {
        if (shift > this->size) {
            shift = this->size;
        }
        if (shift < 2) {
            shift = 2;
        }
        for (auto l = 1; l <= shift; l++) {
            movel(l, amount);
        }
    }

    void FaceletCubeNNN::moveBw(int shift, int amount) {
        if (shift > this->size) {
            shift = this->size;
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

    ostream& operator<<(ostream &os, const FaceletCubeNNN &fc) {
        return os << "FaceletCubeNNN(" << fc.size << ")" << endl << fc.prettify();
    }
}
