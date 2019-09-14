#include<cube_util/CubieCube222.hpp>
#include<cube_util/FaceletCubeNNN.hpp>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    using namespace constants;
    using namespace cube222;
    using namespace utils;

    CubieCube222::CubieCube222():
        perm {URF, UFL, ULB, UBR, DLF, DFR, DRB, DBL},
        twist {T_ORIENTED} {
    }

    CubieCube222::CubieCube222(array<uint16_t, N_CORNER> perm, array<uint16_t, N_CORNER> twist) {

        int twistsTotal = 0;
        uint16_t mask = 0;

        for (auto i = 0; i < N_CORNER; i++) {
            // (a & 0xfff8) != 0 is equivalent to a > 7 for uint16_t
            if ((perm[i] & 0xfff8) != 0 || (mask & (1 << perm[i])) != 0) {
                throw invalid_argument("invalid permutation!");
            }
            mask |= 1 << perm[i];
            if (twist[i] < 0 || twist[i] > 2) {
                throw invalid_argument("invalid orientation!");
            }
            twistsTotal += twist[i];

            // assume all things are good, if we find something is wrong later, we throw an
            // exception
            this->perm[i] = perm[i];
            this->twist[i] = twist[i];
        }

        if (twistsTotal % 3 != 0) {
            throw invalid_argument("wrong orientation!");
        }
    }

    CubieCube222::CubieCube222(uint16_t perm, uint16_t twist) {
        if (perm >= N_PERM || twist >= N_TWIST) {
            throw invalid_argument("invalid parameters!");
        }
        this->setPerm(perm);
        this->setTwist(twist);
    }

    CubieCube222::CubieCube222(uint32_t index): CubieCube222(index / N_TWIST, index % N_TWIST) {

    }

    ostream& operator<<(ostream &os, const CubieCube222 &cc) {
        os << "Perms:";
        for (auto i = 0; i < N_CORNER; i++) {
            os << " " << cc.perm[i];
        }
        os << endl << "Twists:";
        for (auto i = 0; i < N_CORNER; i++) {
            os << " " << cc.twist[i];
        }
        return os << endl;
    }

    void CubieCube222::move(int move) {
        if (move < 0) {
            move = N_MOVE - ((-move) % N_MOVE);
        }
        move %= N_MOVE;
        cubeMult(*this, MOVE_CUBES[move], *this);
    }

    uint64_t CubieCube222::getPerm() {
        return getNPerm(this->perm, N_CORNER - 1);
    }

    void CubieCube222::setPerm(uint64_t index) {
        setNPerm(this->perm, index, N_CORNER - 1);
    }

    uint16_t CubieCube222::getTwist() {
        return getNTwist(this->twist, N_CORNER - 1);
    }

    void CubieCube222::setTwist(uint16_t index) {
        setNTwist(this->twist, index, N_CORNER - 1);
    }

    void CubieCube222::cubeMult(CubieCube222 one, CubieCube222 another, CubieCube222 &result) {
        auto perm = array<uint16_t, N_CORNER>();
        auto twist = array<uint16_t, N_CORNER>();
        for (auto i = 0; i < N_CORNER; i++) {
            perm[i] = one.perm[another.perm[i]];
            twist[i] = (one.twist[another.perm[i]] + another.twist[i]) % 3;
        }
        result.perm = perm;
        result.twist = twist;
    }

    CubieCube222 CubieCube222::fromFaceletCube(FaceletCubeNNN fc) {
        if (fc.getSize() != 2) {
            throw invalid_argument("needs a 2x2x2 cube!");
        }
        auto f = fc.getFacelets();
        array<uint16_t, N_CORNER> perm;
        array<uint16_t, N_CORNER> twist;
        uint16_t color1, color2, ori;
        for (auto i = 0; i < N_CORNER; i++) {
            for (ori = 0; ori < 3; ori++) {
                if (f[FACELET_MAP[i][ori]] == U || f[FACELET_MAP[i][ori]] == D) {
                    break;
                }
            }
            color1 = f[FACELET_MAP[i][(ori + 1) % 3]];
            color2 = f[FACELET_MAP[i][(ori + 2) % 3]];
            for (auto j = 0; j < N_CORNER; j++) {
                if (color1 == FACELET_MAP[j][1] / FACELET_PER_FACE &&
                    color2 == FACELET_MAP[j][2] / FACELET_PER_FACE) {
                    perm[i] = j;
                    twist[i] = ori;
                    break;
                }
            }

        }
        return CubieCube222(perm, twist);
    }

    FaceletCubeNNN CubieCube222::toFaceletCube() {
        auto f = vector<uint16_t>(N_FACE * FACELET_PER_FACE);
        for (auto i = 0; i < N_CORNER; i++) {
            auto piece = perm[i];
            auto orient = twist[i];
            for (auto j = 0; j < 3; j++) {
                f[FACELET_MAP[i][(j + orient) % 3]] = FACELET_MAP[piece][j] / FACELET_PER_FACE;
            }
        }
        return FaceletCubeNNN(2, f);
    }
}
