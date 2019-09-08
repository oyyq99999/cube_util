#ifndef CUBE_UTIL_UTILS_HPP
#define CUBE_UTIL_UTILS_HPP

using namespace std;

namespace cube_util {
    namespace constants {

        const int MAX_SIZE = 33;

        // Colors
        const int U = 0;
        const int R = 1;
        const int F = 2;
        const int D = 3;
        const int L = 4;
        const int B = 5;

        const string FACELET_NAMES = "URFDLB";
    }

    namespace utils {

        template<typename T>
        void cycle4(T* arr, int a, int b, int c, int d) {
            T tmp = arr[a];
            arr[a] = arr[d];
            arr[d] = arr[c];
            arr[c] = arr[b];
            arr[b] = tmp;
        }

        function<int ()> randomizer(int start, int end);
        string scrambleString(int cubeSize, int length);
        string scrambleString(int cubeSize);

    }
}

#endif // CUBE_UTIL_UTILS_HPP
