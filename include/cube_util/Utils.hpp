#ifndef CUBE_UTIL_UTILS_HPP
#define CUBE_UTIL_UTILS_HPP
#include<string>

using namespace std;

namespace cube_util {

    ////////////////////////////////////////////////////////////////////////////
    /// Constants used in the project
    ////////////////////////////////////////////////////////////////////////////
    namespace constants {

        /** Max cube size limited to a reasonable number */
        const int MAX_SIZE = 33;

        // Colors
        const int U = 0; /**< A sticker with U face color */
        const int R = 1; /**< A sticker with R face color */
        const int F = 2; /**< A sticker with F face color */
        const int D = 3; /**< A sticker with D face color */
        const int L = 4; /**< A sticker with L face color */
        const int B = 5; /**< A sticker with B face color */

        /** Facelet names in order */
        const string FACELET_NAMES = "URFDLB";

        /** Number of corners in a cube */
        const int N_CORNER = 8;

        // Corners
        const int URF = 0; /**< URF corner */
        const int UFL = 1; /**< UFL corner */
        const int ULB = 2; /**< ULB corner */
        const int UBR = 3; /**< UBR corner */
        const int DLF = 4; /**< DLF corner */
        const int DFR = 5; /**< DFR corner */
        const int DRB = 6; /**< DRB corner */
        const int DBL = 7; /**< DBL corner */

        const int T_ORIENTED = 0; /**< Corner is oriented **/
        const int T_CLOCKWISE = 1; /**< Corner is twisted clockwise **/
        const int T_COUNTER_CLOCKWISE = 2; /**< Corner is twisted counter-clockwise **/

        // Moves
        const int Ux1 = 0; /**< U move */
        const int Ux2 = 1; /**< U2 move */
        const int Ux3 = 2; /**< U' move */
        const int Rx1 = 3; /**< R move */
        const int Rx2 = 4; /**< R2 move */
        const int Rx3 = 5; /**< R' move */
        const int Fx1 = 6; /**< F move */
        const int Fx2 = 7; /**< F2 move */
        const int Fx3 = 8; /**< F' move */
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Constants used for 2x2x2 cube
    ////////////////////////////////////////////////////////////////////////////
    namespace cube222 {

        /** Type of moves for a 2x2 cube */
        const int N_MOVE = 9;
        /** Total orientations count of first 6 cubies of a 2x2 cube. */
        const int N_TWIST = 729; // 3 ^ 6
        /** Total permutations count of first 7 cubies of a 2x2 cube. */
        const int N_PERM = 5040; // 7!
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Auxiliary functions etc.
    ////////////////////////////////////////////////////////////////////////////
    namespace utils {

        /**
         * Auxiliary function to cycle 4 pieces.
         * It cycles pieces from `a` to `b` to `c` to `d` then back to `a`
         * @param[inout] arr object to cycle
         * @param a index of first element
         * @param b index of second element
         * @param c index of third element
         * @param d index of fourth element
         */
        template<typename T>
        void cycle4(T* arr, int a, int b, int c, int d) {
            T tmp = arr[a];
            arr[a] = arr[d];
            arr[d] = arr[c];
            arr[c] = arr[b];
            arr[b] = tmp;
        }

        /**
         * Calculate permutation index based on given fixed-length permutation.
         * @param arr permutation array
         * @param n number of elements to calculate, n <= 16
         * @returns index of the given permutation
         */
        template<size_t SIZE>
        uint64_t getNPerm(array<uint16_t, SIZE> arr, int n) {
            uint64_t index = 0;
            uint64_t val = 0xFEDCBA9876543210;
            for (auto i = 0; i < n - 1; i++) {
                auto v = arr[i] << 2;
                index = (n - i) * index + (val >> v & 0xf);
                val -= 0x1111111111111110 << v;
            }
            return index;
        }

        /**
         * Calculate fixed-length permutation based on given index.
         * @param[out] arr permutation array
         * @param index given index
         * @param n number of elements in the permutation, n <= 16
         */
        template<size_t SIZE>
        void setNPerm(array<uint16_t, SIZE> &arr, uint64_t index, int n) {
            uint64_t val = 0xFEDCBA9876543210;
            uint64_t extract = 0;
            for (auto p = 2; p <= n; p++) {
                extract = extract << 4 | index % p;
                index /= p;
            }
            for (auto i = 0; i < n - 1; i++) {
                uint16_t v = (extract & 0xf) << 2;
                extract >>= 4;
                arr[i] = val >> v & 0xf;
                uint64_t m = (1 << v) - 1;
                val = (val & m) | (val >> 4 & ~m);
            }
            arr[n - 1] = val & 0xf;
        }

        /**
         * Calculate twist index based on given fixed-length orientation.
         * @param arr orientation array
         * @param n number of elements to calculate, n <= 10
         * @returns index of the given orientation
         */
        template<size_t SIZE>
        uint16_t getNTwist(array<uint16_t, SIZE> arr, int n) {
            uint16_t index = 0;
            for (auto i = 0; i < n - 1; i++) {
                index *= 3;
                index += arr[i];
            }
            return index;
        }

        /**
         * Calculate fixed-length orientation based on given index.
         * @param[out] arr orientation array
         * @param index given index
         * @param n number of elements in the orientation, n <= 10
         */
        template<size_t SIZE>
        void setNTwist(array<uint16_t, SIZE> &arr, uint16_t index, int n) {
            int twist = 0;
            for (auto i = n - 2; i >= 0; i--) {
                arr[i] = index % 3;
                twist += arr[i];
                index /= 3;
            }
            arr[n - 1] = (3 - twist % 3) % 3;
        }

        /**
         * Get a random generator which returns a random int between
         * `start` and `end` (inclusive).
         * @param start lower bound of random range
         * @param end upper bound of random range
         * @returns a function<int ()> which returns a random int on each call
         */
        function<int ()> randomizer(int start, int end);

        /**
         * Generate a scramble sequence string for specified cube size and
         * scramble length.
         * @param cubeSize size of the cube
         * @param length length of the scramble sequence
         * @returns generated scramble string
         */
        string scrambleString(int cubeSize, int length);

        /**
         * Generate a scramble sequence string for specified cube size with
         * a default length.
         * @param cubeSize size of the cube
         * @returns generated scramble string
         */
        string scrambleString(int cubeSize);

    }
}

#endif // CUBE_UTIL_UTILS_HPP
