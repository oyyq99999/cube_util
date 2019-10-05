// Copyright 2019 Yunqi Ouyang
#include<cube_util/Utils.hpp>
#include<random>
#include<array>
#include<boost/algorithm/string/trim.hpp>
#include<cube_util/Scrambler222.hpp>

namespace cube_util {

namespace utils {

    using std::random_device;
    using std::default_random_engine;
    using std::uniform_int_distribution;
    using std::to_string;
    using std::array;

    using boost::trim;

    using constants::N_CHOOSE_MAX;
    using constants::N_MOVE_PER_AXIS;
    using constants::N_MOVE_PER_SHIFT;

    uint32_t choose(uint16_t n, uint16_t k) {
        static const auto cnk = [] {
            auto ret =
                array<array<uint32_t, N_CHOOSE_MAX + 1>, N_CHOOSE_MAX + 1>();
            for (auto i = 0; i <= N_CHOOSE_MAX; i++) {
                ret[i][0] = ret[i][i] = 1;
                for (auto j = 1; j < i; j++) {
                    ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
                }
            }
            return ret;
        }();
        return cnk[n][k];
    }

    bool getNParity(uint64_t index, uint16_t n) {
        uint16_t p = 0;
        for (auto i = n - 2; i >= 0; i--) {
            p ^= index % (n - i);
            index /= (n - i);
        }
        return p & 1;
    }

    function<int64_t()> randomizer(int64_t start, int64_t end) {
        static random_device rd;
        default_random_engine gen = default_random_engine(rd());
        uniform_int_distribution<int64_t> dist(start, end);
        return bind(dist, gen);
    }

    string scrambleString(int cubeSize, int length) {
        using cube222::N_MAX_LENGTH;

        if (cubeSize == 2) {
            length = length > N_MAX_LENGTH ? N_MAX_LENGTH : length;
            return Scrambler222(length).scramble()->toString();
        }
        string scr;
        int count = 0;
        int lastAxis = -1;
        auto turned = vector<bool>(cubeSize - 1, false);
        auto r = randomizer(0, 3 * N_MOVE_PER_AXIS * (cubeSize - 1) - 1);
        while (count < length) {
            auto move = r();
            auto axis = (move / N_MOVE_PER_AXIS) % 3;
            auto shift = move / N_MOVE_PER_SHIFT;
            if (axis != lastAxis) {
                fill(turned.begin(), turned.end(), false);
            } else {
                if (turned[shift] == true) {
                    continue;
                }
            }
            turned[shift] = true;
            lastAxis = axis;
            scr.append(move2Str(move)).append(" ");
            count++;
        }
        trim(scr);
        return scr;
    }

    string scrambleString(int cubeSize) {
        if (cubeSize == 2) {
            return scrambleString(2, cube222::N_MAX_LENGTH);
        }
        if (cubeSize == 3) {
            return scrambleString(cubeSize, 25);
        }
        return scrambleString(cubeSize, (cubeSize - 2) * 20);
    }

    uint16_t reverseMove(uint16_t move) {
        auto amount = move % N_MOVE_PER_AXIS;
        move /= N_MOVE_PER_AXIS;
        move *= N_MOVE_PER_AXIS;
        return move + (N_MOVE_PER_AXIS - 1 - amount);
    }

    string move2Str(uint16_t move) {
        using constants::FACE_NAMES;

        auto shift = move / N_MOVE_PER_SHIFT;
        shift++;

        move %= N_MOVE_PER_SHIFT;
        int axis = move / N_MOVE_PER_AXIS;
        int amount = move % N_MOVE_PER_AXIS;
        string m;

        if (shift > 2) {
            m.append(to_string(shift));
        }
        m.append(&FACE_NAMES[axis], 1);
        if (shift >= 2) {
            m.append("w");
        }
        m.append(&" 2'"[amount], 1);
        trim(m);
        return m;
    }
}  // namespace utils
}  // namespace cube_util
