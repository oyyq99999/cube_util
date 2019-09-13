#include<functional>
#include<random>
#include<iostream>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    namespace utils {

        using namespace constants;

        function<int ()> randomizer(int start, int end) {
            random_device rd;
            default_random_engine gen = default_random_engine(rd());
            uniform_int_distribution<int> dist(start, end);
            return bind(dist, gen);
        }

        string scrambleString(int cubeSize, int length) {
            string scr;
            int count = 0;
            int lastAxis = -1;
            bool turned[cubeSize - 1];
            auto r = randomizer(0, 3 * 3 * (cubeSize - 1) - 1);
            while (count < length) {
                auto move = r();
                auto axis = (move / N_MOVE_PER_AXIS) % 3;
                auto shift = move / N_MOVE_PER_SHIFT;
                if (axis != lastAxis) {
                    fill_n(turned, cubeSize - 1, false);
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
            return trim(scr);
        }

        string scrambleString(int cubeSize) {
            if (cubeSize <= 3) {
                return scrambleString(cubeSize, 25);
            }
            return scrambleString(cubeSize, (cubeSize - 2) * 20);
        }

        string trim(string s) {
            // trim from start
            s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
                return !isspace(ch);
            }));
            // trim from end
            s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
                return !isspace(ch);
            }).base(), s.end());
            return s;
        }

        uint16_t reverseMove(uint16_t move) {
            auto amount = move % N_MOVE_PER_AXIS;
            move /= N_MOVE_PER_AXIS;
            move *= N_MOVE_PER_AXIS;
            return move + (N_MOVE_PER_AXIS - 1 - amount);
        }

        string move2Str(uint16_t move) {
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
            return trim(m);
        }
    }
}
