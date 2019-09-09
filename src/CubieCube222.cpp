#include<cube_util/CubieCube222.hpp>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    using namespace constants;
    using namespace cube222;

    CubieCube222::CubieCube222():
        perm {URF, UFL, ULB, UBR, DLF, DFR, DRB, DBL},
        twist {T_ORIENTED} {
    }

    CubieCube222::CubieCube222(array<uint16_t, N_CORNERS> perm, array<uint16_t, N_CORNERS> twist) {

        int twistsTotal = 0;
        uint16_t mask = 0;

        for (auto i = 0; i < N_CORNERS; i++) {
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

    ostream& operator<<(ostream &os, const CubieCube222 &cc) {
        os << "Perms:";
        for (auto i = 0; i < N_CORNERS; i++) {
            os << " " << cc.perm[i];
        }
        os << endl << "Twists:";
        for (auto i = 0; i < N_CORNERS; i++) {
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

    void CubieCube222::cubeMult(CubieCube222 one, CubieCube222 another, CubieCube222 &result) {
        auto perm = array<uint16_t, N_CORNERS>();
        auto twist = array<uint16_t, N_CORNERS>();
        for (auto i = 0; i < N_CORNERS; i++) {
            perm[i] = one.perm[another.perm[i]];
            twist[i] = (one.twist[another.perm[i]] + another.twist[i]) % 3;
        }
        result.perm = perm;
        result.twist = twist;
    }

    const array<CubieCube222, N_MOVE> CubieCube222::MOVE_CUBES = [] {
        auto ret = array<CubieCube222, N_MOVE>();
        ret[Ux1] = CubieCube222({3, 0, 1, 2, 4, 5, 6, 7}, {0});
        ret[Rx1] = CubieCube222({5, 1, 2, 0, 4, 6, 3, 7}, {2, 0, 0, 1, 0, 1, 2, 0});
        ret[Fx1] = CubieCube222({1, 4, 2, 3, 5, 0, 6, 7}, {1, 2, 0, 0, 1, 2, 0, 0});

        for (auto i = 0; i < N_MOVE; i+=3) {
            for (auto j = 1; j < 3; j++) {
                ret[i + j] = CubieCube222();
                cubeMult(ret[i + j - 1], ret[i], ret[i + j]);
            }
        }
        return ret;
    }();
}
