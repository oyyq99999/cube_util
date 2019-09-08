#include<functional>
#include<random>
#include<iostream>
#include<cube_util/Utils.hpp>

using namespace std;
using namespace cube_util::constants;

namespace cube_util {
    namespace utils {

        function<int ()> randomizer(int start, int end) {
            random_device rd;
            default_random_engine gen = default_random_engine(rd());
            uniform_int_distribution<int> dist(start, end);
            return bind(dist, gen);
        }

        string scrambleString(int cubeSize, int length) {
            string scr = "";
            int count = 0;
            int lastAxis = -1;
            bool turned[3 * (cubeSize - 1)];
            fill_n(turned, 3 * (cubeSize - 1), false);
            auto rAxis = randomizer(0, 2);
            auto rShift = randomizer(0, cubeSize - 2);
            auto rAmount = randomizer(0, 2);
            while (count < length) {
                int axis = rAxis();
                int shift = rShift();
                if (axis != lastAxis) {
                    if (lastAxis != -1) {
                        fill_n(turned + lastAxis * (cubeSize - 1), (lastAxis + 1) * (cubeSize - 1), false);
                    }
                } else {
                    if (turned[axis * (cubeSize - 1) + shift] == true) {
                        continue;
                    }
                }
                int amount = rAmount();
                turned[axis * (cubeSize - 1) + shift] = true;
                lastAxis = axis;
                if (shift >= cubeSize >> 1) {
                    axis += 3;
                    shift -= cubeSize >> 1;
                }
                shift++;
                if (shift > 2) {
                    scr.append(to_string(shift));
                }
                scr.append(&FACELET_NAMES[axis], 1);
                if (shift >= 2) {
                    scr.append("w");
                }
                scr.append(&" 2'"[amount], 1);
                if (amount > 0) {
                    scr.append(" ");
                }
                count++;
            }
            return scr;
        }

        string scrambleString(int cubeSize) {
            if (cubeSize <= 3) {
                return scrambleString(cubeSize, 25);
            }
            return scrambleString(cubeSize, (cubeSize - 2) * 20);
        }
    }
}
