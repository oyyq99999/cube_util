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
        const uint16_t MAX_SIZE = 33;

        /** Number of axis in a cube */
        const uint16_t N_AXIS = 6;

        /** Number of face in a cube */
        const uint16_t N_FACE = 6;

        // Colors
        const uint16_t U = 0; /**< A sticker with U face color */
        const uint16_t R = 1; /**< A sticker with R face color */
        const uint16_t F = 2; /**< A sticker with F face color */
        const uint16_t D = 3; /**< A sticker with D face color */
        const uint16_t L = 4; /**< A sticker with L face color */
        const uint16_t B = 5; /**< A sticker with B face color */

        /** Facelet names in order */
        const string FACE_NAMES = "URFDLB";

        /** Number of corners in a cube */
        const uint16_t N_CORNER = 8;

        // Corners
        const uint16_t URF = 0; /**< URF corner */
        const uint16_t UFL = 1; /**< UFL corner */
        const uint16_t ULB = 2; /**< ULB corner */
        const uint16_t UBR = 3; /**< UBR corner */
        const uint16_t DLF = 4; /**< DLF corner */
        const uint16_t DFR = 5; /**< DFR corner */
        const uint16_t DRB = 6; /**< DRB corner */
        const uint16_t DBL = 7; /**< DBL corner */

        const uint16_t T_ORIENTED = 0; /**< Corner is oriented **/
        const uint16_t T_CLOCKWISE = 1; /**< Corner is twisted clockwise **/
        const uint16_t T_COUNTER_CLOCKWISE = 2; /**< Corner is twisted counter-clockwise **/

        /** Possible move amount types for an axis */
        const uint16_t N_MOVE_PER_AXIS = 3;
        /** Possible move types for a fixed shift */
        const uint16_t N_MOVE_PER_SHIFT = N_MOVE_PER_AXIS * N_AXIS;

        // Moves
        const uint16_t Ux1 = 0; /**< U move */
        const uint16_t Ux2 = 1; /**< U2 move */
        const uint16_t Ux3 = 2; /**< U' move */
        const uint16_t Rx1 = 3; /**< R move */
        const uint16_t Rx2 = 4; /**< R2 move */
        const uint16_t Rx3 = 5; /**< R' move */
        const uint16_t Fx1 = 6; /**< F move */
        const uint16_t Fx2 = 7; /**< F2 move */
        const uint16_t Fx3 = 8; /**< F' move */
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Constants used for 2x2x2 cube
    ////////////////////////////////////////////////////////////////////////////
    namespace cube222 {

        /** Type of moves for a 2x2x2 cube */
        const uint16_t N_MOVE = 9;
        /** Total orientations count of first 6 cubies of a 2x2x2 cube. */
        const uint16_t N_TWIST = 729; // 3 ^ 6
        /** Total permutations count of first 7 cubies of a 2x2x2 cube. */
        const uint16_t N_PERM = 5040; // 7!
        /** God's number of a 2x2x2 cube */
        const uint16_t N_MAX_LENGTH = 11;

        /** Permutation index of solved permutation */
        const uint16_t SOLVED_PERM = 0;
        /** Orientation index of solved orientation */
        const uint16_t SOLVED_TWIST = 0;

        /** Number of stickers on a face */
        const uint16_t FACELET_PER_FACE = 4;
        // Facelets
        const uint16_t U1 = 0; /**< 1st sticker on U */
        const uint16_t U2 = 1; /**< 2nd sticker on U */
        const uint16_t U3 = 2; /**< 3rd sticker on U */
        const uint16_t U4 = 3; /**< 4th sticker on U */
        const uint16_t R1 = 4; /**< 1st sticker on R */
        const uint16_t R2 = 5; /**< 2nd sticker on R */
        const uint16_t R3 = 6; /**< 3rd sticker on R */
        const uint16_t R4 = 7; /**< 4th sticker on R */
        const uint16_t F1 = 8; /**< 1st sticker on F */
        const uint16_t F2 = 9; /**< 2nd sticker on F */
        const uint16_t F3 = 10; /**< 3rd sticker on F */
        const uint16_t F4 = 11; /**< 4th sticker on F */
        const uint16_t D1 = 12; /**< 1st sticker on D */
        const uint16_t D2 = 13; /**< 2nd sticker on D */
        const uint16_t D3 = 14; /**< 3rd sticker on D */
        const uint16_t D4 = 15; /**< 4th sticker on D */
        const uint16_t L1 = 16; /**< 1st sticker on L */
        const uint16_t L2 = 17; /**< 2nd sticker on L */
        const uint16_t L3 = 18; /**< 3rd sticker on L */
        const uint16_t L4 = 19; /**< 4th sticker on L */
        const uint16_t B1 = 20; /**< 1st sticker on B */
        const uint16_t B2 = 21; /**< 2nd sticker on B */
        const uint16_t B3 = 22; /**< 3rd sticker on B */
        const uint16_t B4 = 23; /**< 4th sticker on B */

        /** Facelet mapping for cubies */
        const uint16_t FACELET_MAP[][3] = {
            {U4, R1, F2}, {U3, F1, L2}, {U1, L1, B2}, {U2, B1, R2},
            {D1, L4, F3}, {D2, F4, R3}, {D4, R4, B3}, {D3, B4, L3}
        };
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Auxiliary functions etc.
    ////////////////////////////////////////////////////////////////////////////
    namespace utils {

        /**
         * Auxiliary function to cycle 4 pieces.
         * It cycles pieces from `a` to `b` to `c` to `d` then back to `a`
         * @param[inout] vec object to cycle
         * @param a index of first element
         * @param b index of second element
         * @param c index of third element
         * @param d index of fourth element
         */
        template<typename T>
        void cycle4(vector<T> &vec, int a, int b, int c, int d) {
            T tmp = vec[a];
            vec[a] = vec[d];
            vec[d] = vec[c];
            vec[c] = vec[b];
            vec[b] = tmp;
        }

        /**
         * Calculate permutation index based on given fixed-length permutation.
         * @param arr permutation array
         * @param n number of elements to calculate, n <= 16
         * @returns index of the given permutation
         */
        template<size_t SIZE>
        uint64_t getNPerm(array<uint16_t, SIZE> arr, uint16_t n) {
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
        void setNPerm(array<uint16_t, SIZE> &arr, uint64_t index, uint16_t n) {
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
        uint16_t getNTwist(array<uint16_t, SIZE> arr, uint16_t n) {
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
        void setNTwist(array<uint16_t, SIZE> &arr, uint16_t index, uint16_t n) {
            int twist = 0;
            for (auto i = n - 2; i >= 0; i--) {
                arr[i] = index % 3;
                twist += arr[i];
                index /= 3;
            }
            arr[n - 1] = (3 - twist % 3) % 3;
        }

        /**
         * Set pruning value into pruning table.
         * Each element of the array contains pruning values for 4 indices.
         * Each pruning value needs to be less than 15.
         * @param[inout] arr table reference
         * @param index pruning index
         * @param p pruning value
         */
        template<size_t SIZE>
        void setPruning(array<uint16_t, SIZE> &arr, uint32_t index, uint16_t p) {
            auto i = index >> 2;
            auto shift = (index & 0x3) << 2;
            auto mask = ~((uint16_t)0xf << shift);
            p &= 0xf;
            arr[i] = (arr[i] & mask) | (p << shift);
        }

        /**
         * Get pruning value from pruning table.
         * Each element of the array contains pruning values for 4 indices.
         * Each pruning value needs to be less than 15.
         * @param arr table reference
         * @param index pruning index
         * @returns the pruning value
         */
        template<size_t SIZE>
        uint16_t getPruning(array<uint16_t, SIZE> arr, uint32_t index) {
            auto i = index >> 2;
            auto shift = (index & 0x3) << 2;
            return (arr[i] >> shift) & 0xf;
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

        /**
         * Return a string by removing heading and trailing whitespaces
         * from `s`.
         * @param s original string
         * @returns trimmed string
         */
        string trim(string s);

        /**
         * Get the reverse of a move.
         * @param move a move
         * @returns reversed move
         */
        uint16_t reverseMove(uint16_t move);

        /**
         * Translate a move code to human-readable move string.
         * @param move numbered move code
         * @returns move name in WCA notation
         */
        string move2Str(uint16_t move);

    }
}

#endif // CUBE_UTIL_UTILS_HPP
