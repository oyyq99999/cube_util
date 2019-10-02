// Copyright 2019 Yunqi Ouyang
#include<cube_util/CubieCube222.hpp>
#include<sstream>

namespace cube_util {

    using std::invalid_argument;
    using std::ostringstream;
    using std::endl;

    using constants::N_FACE;

    using enums::Colors::U;
    using enums::Colors::D;

    using enums::CornerTwists::ORIENTED;
    using enums::CornerTwists::COUNTER_CLOCKWISE;

    using cube222::FACELET_PER_FACE;
    using cube222::FACELET_MAP;

    using utils::setNPerm;
    using utils::getNPerm;
    using utils::setNTwist;
    using utils::getNTwist;
    using utils::randomizer;

    CubieCube222::CubieCube222(array<uint16_t, N_CORNER> perm,
        array<uint16_t, N_CORNER> twist) {
        int twistsTotal = 0;
        uint16_t mask = 0;

        for (auto i = 0; i < N_CORNER; i++) {
            // (a & 0xfff8) != 0 is equivalent to a > 7 for uint16_t
            if ((perm[i] & 0xfff8) != 0 || (mask & (1 << perm[i])) != 0) {
                throw invalid_argument("invalid permutation!");
            }
            mask |= 1 << perm[i];
            if (twist[i] < ORIENTED || twist[i] > COUNTER_CLOCKWISE) {
                throw invalid_argument("invalid orientation!");
            }
            twistsTotal += twist[i];

            // assume all things are good, if we find something is wrong later,
            // we throw an exception
            this->cp[i] = perm[i];
            this->co[i] = twist[i];
        }

        if (twistsTotal % 3 != 0) {
            throw invalid_argument("wrong orientation!");
        }
    }

    CubieCube222::CubieCube222(uint16_t perm, uint16_t twist) {
        if (perm >= N_PERM || twist >= N_TWIST) {
            throw invalid_argument("invalid parameters!");
        }
        this->setCP(perm);
        this->setCO(twist);
    }

    CubieCube222::CubieCube222(uint32_t index):
        CubieCube222(index / N_TWIST, index % N_TWIST) {}

    void CubieCube222::setCP(uint16_t index) {
        setNPerm(&this->cp, index, N_CORNER - 1);
    }

    void CubieCube222::setCO(uint16_t index) {
        setNTwist(&this->co, index, N_CORNER - 1);
    }

    uint16_t CubieCube222::getCP() const {
        return getNPerm(this->cp, N_CORNER - 1);
    }

    uint16_t CubieCube222::getCO() const {
        return getNTwist(this->co, N_CORNER - 1);
    }

    void CubieCube222::move(uint16_t move) {
        move %= N_MOVE;
        cubeMult(*this, MOVE_CUBES[move], this);
    }

    void CubieCube222::cubeMult(CubieCube222 one, CubieCube222 another,
        CubieCube222 *result) {
        auto perm = array<uint16_t, N_CORNER>();
        auto twist = array<uint16_t, N_CORNER>();
        for (auto i = 0; i < N_CORNER; i++) {
            perm[i] = one.cp[another.cp[i]];
            twist[i] = (one.co[another.cp[i]] + another.co[i]) % 3;
        }
        result->cp = perm;
        result->co = twist;
    }

    string CubieCube222::toString() const {
        ostringstream os;
        os << "Perms:";
        for (auto i = 0; i < N_CORNER; i++) {
            os << " " << cp[i];
        }
        os << endl << "Twists:";
        for (auto i = 0; i < N_CORNER; i++) {
            os << " " << co[i];
        }
        os << endl;
        return os.str();
    }

    FaceletCubeNNN CubieCube222::toFaceletCube() {
        auto f = vector<uint16_t>(N_FACE * FACELET_PER_FACE);
        for (auto i = 0; i < N_CORNER; i++) {
            auto piece = cp[i];
            auto orient = co[i];
            for (auto j = 0; j < 3; j++) {
                f[FACELET_MAP[i][(j + orient) % 3]]
                    = FACELET_MAP[piece][j] / FACELET_PER_FACE;
            }
        }
        return FaceletCubeNNN(2, f);
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
                if (f[FACELET_MAP[i][ori]] == U
                    || f[FACELET_MAP[i][ori]] == D) {
                    break;
                }
            }
            color1 = f[FACELET_MAP[i][(ori + 1) % 3]];
            color2 = f[FACELET_MAP[i][(ori + 2) % 3]];
            for (auto j = 0; j < N_CORNER; j++) {
                if (color1 == FACELET_MAP[j][1] / FACELET_PER_FACE
                    && color2 == FACELET_MAP[j][2] / FACELET_PER_FACE) {
                    perm[i] = j;
                    twist[i] = ori;
                    break;
                }
            }
        }
        return CubieCube222(perm, twist);
    }

    CubieCube222 CubieCube222::randomCube() {
        auto r = randomizer(0, N_TWIST * N_PERM - 1);
        return CubieCube222(r());
    }
}  // namespace cube_util
