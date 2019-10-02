// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_UTILS_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_UTILS_HPP_
#include<cstdint>
#include<string>
#include<vector>

namespace cube_util {

    using std::string;

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

    /** Facelet names in order */
    const string FACE_NAMES = "URFDLB";

    /** Number of corners in a cube */
    const uint16_t N_CORNER = 8;

    /** Possible move amount types for an axis */
    const uint16_t N_MOVE_PER_AXIS = 3;
    /** Possible move types for a fixed shift */
    const uint16_t N_MOVE_PER_SHIFT = N_MOVE_PER_AXIS * N_AXIS;
}  // namespace constants

////////////////////////////////////////////////////////////////////////////
/// Enumerations used in the project
////////////////////////////////////////////////////////////////////////////
namespace enums {

    /** Sticker colors */
    enum Colors {
        U, R, F, D, L, B,
    };

    /** Corner numbers */
    enum Corners {
        URF, UFL, ULB, UBR, DLF, DFR, DRB, DBL,
    };

    /** Corner orientation representations */
    enum CornerTwists {
        ORIENTED, CLOCKWISE, COUNTER_CLOCKWISE,
    };

    /** Part of applicable moves */
    enum Moves {
        Ux1, Ux2, Ux3, Rx1, Rx2, Rx3, Fx1, Fx2, Fx3,
        Dx1, Dx2, Dx3, Lx1, Lx2, Lx3, Bx1, Bx2, Bx3,
        Uw1, Uw2, Uw3, Rw1, Rw2, Rw3, Fw1, Fw2, Fw3,
        Dw1, Dw2, Dw3, Lw1, Lw2, Lw3, Bw1, Bw2, Bw3,
        _3Uw1, _3Uw2, _3Uw3, _3Rw1, _3Rw2, _3Rw3, _3Fw1, _3Fw2, _3Fw3,
        _3Dw1, _3Dw2, _3Dw3, _3Lw1, _3Lw2, _3Lw3, _3Bw1, _3Bw2, _3Bw3,
    };
}  // namespace enums

////////////////////////////////////////////////////////////////////////////
/// Constants used for 2x2x2 cube
////////////////////////////////////////////////////////////////////////////
namespace cube222 {

    /** Type of moves for a 2x2x2 cube */
    const uint16_t N_MOVE = 9;
    /** Total orientations count of first 6 cubies of a 2x2x2 cube. */
    const uint16_t N_TWIST = 729;  // 3 ^ 6
    /** Total permutations count of first 7 cubies of a 2x2x2 cube. */
    const uint16_t N_PERM = 5040;  // 7!
    /** God's number of a 2x2x2 cube */
    const uint16_t N_MAX_LENGTH = 11;

    /** Permutation index of solved permutation */
    const uint16_t SOLVED_PERM = 0;
    /** Orientation index of solved orientation */
    const uint16_t SOLVED_TWIST = 0;

    /** Number of stickers on a face */
    const uint16_t FACELET_PER_FACE = 4;

    /** Facelets on each face */
    enum Facelets {
        U1, U2, U3, U4,
        R1, R2, R3, R4,
        F1, F2, F3, F4,
        D1, D2, D3, D4,
        L1, L2, L3, L4,
        B1, B2, B3, B4,
    };

    /** Facelet mapping for cubies */
    const uint16_t FACELET_MAP[][3] = {
        {U4, R1, F2}, {U3, F1, L2}, {U1, L1, B2}, {U2, B1, R2},
        {D1, L4, F3}, {D2, F4, R3}, {D4, R4, B3}, {D3, B4, L3}
    };
}  // namespace cube222

////////////////////////////////////////////////////////////////////////////
/// Auxiliary functions etc.
////////////////////////////////////////////////////////////////////////////
namespace utils {

    using std::array;
    using std::vector;
    using std::function;

    /**
     * Auxiliary function to cycle 4 pieces.
     * It cycles pieces from `a` to `b` to `c` to `d` then back to `a`
     * @param[inout] *vec pointer to object to cycle
     * @param a index of first element
     * @param b index of second element
     * @param c index of third element
     * @param d index of fourth element
     */
    template<typename T>
    void cycle4(vector<T> *vec, int a, int b, int c, int d) {
        T tmp = (*vec)[a];
        (*vec)[a] = (*vec)[d];
        (*vec)[d] = (*vec)[c];
        (*vec)[c] = (*vec)[b];
        (*vec)[b] = tmp;
    }

    /**
     * Calculate permutation index based on given fixed-length permutation.
     * @param arr permutation array
     * @param n number of elements to calculate, n <= 16
     * @returns index of the given permutation
     */
    template<size_t SIZE>
    uint64_t getNPerm(array<uint16_t, SIZE> arr, uint16_t n) {
        uint64_t index = 0UL;
        uint64_t val = 0xFEDCBA9876543210UL;
        for (auto i = 0; i < n - 1; i++) {
            auto v = arr[i] << 2;
            index = (n - i) * index + (val >> v & 0xf);
            val -= 0x1111111111111110UL << v;
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
    void setNPerm(array<uint16_t, SIZE> *arr, uint64_t index, uint16_t n) {
        uint64_t val = 0xFEDCBA9876543210UL;
        uint64_t extract = 0UL;
        for (auto p = 2; p <= n; p++) {
            extract = extract << 4 | index % p;
            index /= p;
        }
        for (auto i = 0; i < n - 1; i++) {
            uint16_t v = (extract & 0xf) << 2;
            extract >>= 4;
            (*arr)[i] = val >> v & 0xf;
            uint64_t m = (1UL << v) - 1;
            val = (val & m) | (val >> 4 & ~m);
        }
        (*arr)[n - 1] = val & 0xf;
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
    void setNTwist(array<uint16_t, SIZE> *arr, uint16_t index, uint16_t n) {
        int twist = 0;
        for (auto i = n - 2; i >= 0; i--) {
            (*arr)[i] = index % 3;
            twist += (*arr)[i];
            index /= 3;
        }
        (*arr)[n - 1] = (3 - twist % 3) % 3;
    }

    /**
     * Set pruning value into pruning table.
     * Each element of the array contains pruning values for 4 indices.
     * Each pruning value needs to be less than 15.
     * @param[inout] *arr table pointer
     * @param index pruning index
     * @param p pruning value
     */
    template<size_t SIZE>
    void setPruning(array<uint16_t, SIZE> *arr, uint32_t index,
        uint16_t p) {
        auto i = index >> 2;
        auto shift = (index & 0x3) << 2;
        auto mask = ~((uint16_t)0xf << shift);
        p &= 0xf;
        (*arr)[i] = ((*arr)[i] & mask) | (p << shift);
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
     * @returns a function<int64_t()> which returns a random int on each call
     */
    function<int64_t()> randomizer(int64_t start, int64_t end);

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

}  // namespace utils
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_UTILS_HPP_
