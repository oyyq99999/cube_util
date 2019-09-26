#include<array>
#include<cube_util/CubieCube222.hpp>
#include<cube_util/Cube222Solver.hpp>

using namespace std;

namespace cube_util {

    using namespace utils;

    const array<CubieCube222, N_MOVE> CubieCube222::MOVE_CUBES = [] {
        auto ret = array<CubieCube222, N_MOVE>();
        ret[Ux1] = CubieCube222({3, 0, 1, 2, 4, 5, 6, 7}, {0});
        ret[Rx1] = CubieCube222({5, 1, 2, 0, 4, 6, 3, 7}, {2, 0, 0, 1, 0, 1, 2, 0});
        ret[Fx1] = CubieCube222({1, 4, 2, 3, 5, 0, 6, 7}, {1, 2, 0, 0, 1, 2, 0, 0});

        for (auto i = 0; i < N_MOVE; i += 3) {
            for (auto j = 1; j < 3; j++) {
                ret[i + j] = CubieCube222();
                cubeMult(ret[i + j - 1], ret[i], ret[i + j]);
            }
        }
        return ret;
    }();

    const array<array<uint16_t, N_MOVE>, N_PERM> CubieCube222::PERM_MOVE = [] {
        auto ret = array<array<uint16_t, N_MOVE>, N_PERM>();
        CubieCube222 c = CubieCube222();
        CubieCube222 d = CubieCube222();
        for (auto i = 0; i < N_PERM; i++) {
            c.setCP(i);
            for (auto j = 0; j < N_MOVE; j++) {
                cubeMult(c, MOVE_CUBES[j], d);
                ret[i][j] = d.getCP();
            }
        }
        return ret;
    }();

    const array<array<uint16_t, N_MOVE>, N_TWIST> CubieCube222::TWIST_MOVE = [] {
        auto ret = array<array<uint16_t, N_MOVE>, N_TWIST>();
        CubieCube222 c = CubieCube222();
        CubieCube222 d = CubieCube222();
        for (auto i = 0; i < N_TWIST; i++) {
            c.setCO(i);
            for (auto j = 0; j < N_MOVE; j++) {
                cubeMult(c, MOVE_CUBES[j], d);
                ret[i][j] = d.getCO();
            }
        }
        return ret;
    }();

    const array<uint16_t, ((N_PERM + 3) >> 2)> Cube222Solver::PERM_PRUNING = [] {
        auto ret = array<uint16_t, ((N_PERM + 3) >> 2)>();
        fill(ret.begin(), ret.end(), 0xffff);
        auto count = 0;
        for (auto depth = 0; count < N_PERM; depth++) {
            if (depth == 0) {
                setPruning(ret, SOLVED_PERM, depth);
                count++;
                continue;
            }
            for (auto perm = 0; perm < N_PERM; perm++) {
                if (getPruning(ret, perm) == depth - 1) {
                    for (auto move = 0; move < N_MOVE; move++) {
                        auto newPerm = CubieCube222::PERM_MOVE[perm][move];
                        if (getPruning(ret, newPerm) == 0xf) {
                            setPruning(ret, newPerm, depth);
                            count++;
                        }
                    }
                }
            }
        }
        return ret;
    }();

    const array<uint16_t, ((N_TWIST + 3) >> 2)> Cube222Solver::TWIST_PRUNING = [] {
        auto ret = array<uint16_t, ((N_TWIST + 3) >> 2)>();
        fill(ret.begin(), ret.end(), 0xffff);
        auto count = 0;
        for (auto depth = 0; count < N_TWIST; depth++) {
            if (depth == 0) {
                setPruning(ret, SOLVED_TWIST, depth);
                count++;
                continue;
            }
            for (auto twist = 0; twist < N_TWIST; twist++) {
                if (getPruning(ret, twist) == depth - 1) {
                    for (auto move = 0; move < N_MOVE; move++) {
                        auto newTwist = CubieCube222::TWIST_MOVE[twist][move];
                        if (getPruning(ret, newTwist) == 0xf) {
                            setPruning(ret, newTwist, depth);
                            count++;
                        }
                    }
                }
            }
        }
        return ret;
    }();
}
