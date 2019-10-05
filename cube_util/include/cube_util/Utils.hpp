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

    /** Max choose range */
    const uint16_t N_CHOOSE_MAX = 24;

    /** Non-existent axis */
    const uint16_t INVALID_AXIS = 0xff;
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
/// Constants used for 3x3x3 cube
////////////////////////////////////////////////////////////////////////////
namespace cube333 {

    using enums::Moves::Ux1;
    using enums::Moves::Ux2;
    using enums::Moves::Ux3;
    using enums::Moves::Rx2;
    using enums::Moves::Fx2;
    using enums::Moves::Dx1;
    using enums::Moves::Dx2;
    using enums::Moves::Dx3;
    using enums::Moves::Lx2;
    using enums::Moves::Bx2;

    /** Type of moves for a 3x3x3 cube */
    const uint16_t N_MOVE = 18;
    /** Total orientations count of first 7 corners of a 3x3x3 cube. */
    const uint16_t N_CORNER_TWIST = 2187;  // 3 ^ 7
    /** Total permutations count of corners of a 3x3x3 cube. */
    const uint16_t N_CORNER_PERM = 40320;  // 8!
    /** Total orientations count of first 11 edges of a 3x3x3 cube. */
    const uint16_t N_EDGE_FLIP = 2048;  // 2 ^ 11
    /** Total permutations count of edges of a 3x3x3 cube. */
    const uint32_t N_EDGE_PERM = 479001600;  // 12!
    /** Total permutations count of UD 8 edges of a 3x3x3 cube. */
    const uint16_t N_UD8EDGE_PERM = 40320;  // 8!
    /** Total E-slice edges positions count of a 3x3x3 cube. */
    const uint16_t N_SLICE_POSITION = 495;  // C(12, 4)
    /** Total permutations count of E-slice edges of a 3x3x3 cube. */
    const uint16_t N_SLICE_EDGE_PERM = 24;  // 4!

    /** Number of edges in a 3x3x3 cube */
    const uint16_t N_EDGE = 12;

    /** Corner permutation index of solved state */
    const uint16_t SOLVED_CP = 0;
    /** Corner orientation index of solved state */
    const uint16_t SOLVED_TWIST = 0;
    /** Edge permutation index of solved state */
    const uint32_t SOLVED_EP = 0;
    /** Edge orientation index of solved state */
    const uint16_t SOLVED_FLIP = 0;
    /** E-slice edges choose index of solved state */
    const uint16_t SOLVED_SLICE_POSITION = 494;  // C(12, 4) - 1;
    /** UD 8 Edge permutation index of solved state */
    const uint32_t SOLVED_UD8_EP = 0;
    /** E-slice edges permutation index of solved state */
    const uint16_t SOLVED_SLICE_EP = 0;
    /** Max solution length for first phase of the two-phase algorithm. */
    const uint16_t N_MAX_PHASE1_LENGTH = 20;
    /** Max solution length for second phase of the two-phase algorithm. */
    const uint16_t N_MAX_PHASE2_LENGTH = 18;
    /** Max solution length for two-phase algorithm. */
    const uint16_t N_MAX_LENGTH = 30;
    /** Max solution length to check if a cube is solvable. */
    const uint16_t N_MAX_CHECK_LENGTH = 11;
    /** Different move types for phase 2 */
    const uint16_t N_PHASE2_MOVE_COUNT = 10;
    /** Possible moves in phase 2 */
    const uint16_t PHASE2_MOVE[] = {Ux1, Ux2, Ux3, Rx2, Fx2,
        Dx1, Dx2, Dx3, Lx2, Bx2};

    /** Number of stickers on a face */
    const uint16_t FACELET_PER_FACE = 9;

    /** Facelets on each face */
    enum Facelets {
        U1, U2, U3, U4, U5, U6, U7, U8, U9,
        R1, R2, R3, R4, R5, R6, R7, R8, R9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9,
        D1, D2, D3, D4, D5, D6, D7, D8, D9,
        L1, L2, L3, L4, L5, L6, L7, L8, L9,
        B1, B2, B3, B4, B5, B6, B7, B8, B9,
    };

    /** Edge numbers */
    enum Edges {
        UF, UL, UB, UR, DF, DR, DB, DL, FL, BL, BR, FR,
    };

    /** Edge orientation representations */
    enum EdgeFlips {
        NOT_FLIPPED, FLIPPED,
    };

    /** Facelet mapping for corners */
    const uint16_t CORNER_FACELET_MAP[][3] = {
        {U9, R1, F3}, {U7, F1, L3}, {U1, L1, B3}, {U3, B1, R3},
        {D1, L9, F7}, {D3, F9, R7}, {D9, R9, B7}, {D7, B9, L7}
    };

    /** Facelet mapping for edges */
    const uint16_t EDGE_FACELET_MAP[][2] = {
        {U8, F2}, {U4, L2}, {U2, B2}, {U6, R2},
        {D2, F8}, {D6, R8}, {D8, B8}, {D4, L8},
        {F4, L6}, {B6, L4}, {B4, R6}, {F6, R4}
    };
}  // namespace cube333

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
    uint64_t getNPerm(const array<uint16_t, SIZE> &arr, uint16_t n) {
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
    uint16_t getNTwist(const array<uint16_t, SIZE> &arr, uint16_t n) {
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
     * Calculate flip index based on given fixed-length orientation.
     * @param arr orientation array
     * @param n number of elements to calculate, n <= 16
     * @returns index of the given orientation
     */
    template<size_t SIZE>
    uint16_t getNFlip(const array<uint16_t, SIZE> &arr, uint16_t n) {
        uint16_t index = 0;
        for (auto i = 0; i < n - 1; i++) {
            index <<= 1;
            index |= arr[i] & 1;
        }
        return index;
    }

    /**
     * Calculate fixed-length orientation based on given index.
     * @param[out] arr orientation array
     * @param index given index
     * @param n number of elements in the orientation, n <= 16
     */
    template<size_t SIZE>
    void setNFlip(array<uint16_t, SIZE> *arr, uint16_t index, uint16_t n) {
        int flip = 0;
        for (auto i = n - 2; i >= 0; i--) {
            (*arr)[i] = index & 1;
            flip ^= (*arr)[i];
            index >>= 1;
        }
        (*arr)[n - 1] = flip;
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
    uint16_t getPruning(const array<uint16_t, SIZE> &arr, uint32_t index) {
        auto i = index >> 2;
        auto shift = (index & 0x3) << 2;
        return (arr[i] >> shift) & 0xf;
    }

    /**
     * Get choose value for no more than constants::N_CHOOSE_MAX elements.
     * @param n total element number
     * @param k how many to choose
     * @return choose value
     */
    uint32_t choose(uint16_t n, uint16_t k);

    /**
     * Calculate combination index of 4 elements position choose
     * out of n in an array.
     * @param arr array to calculate
     * @param n number of array elements
     * @param mask first element in the array, must be multiple of 4
     * @returns index order of the combination
     */
    template<size_t SIZE>
    uint16_t getNComb4(const array<uint16_t, SIZE> &arr, uint16_t n,
        uint16_t mask) {
        auto end = n - 1;
        auto index = 0, r = 4;
        for (auto i = end; i >= 0; i--) {
            auto v = arr[i];
            if ((v & 0xc) == mask) {
                index += choose(i, r--);
            }
        }
        return index;
    }

    /**
     * Set choose of 4 elements out of n in an array based on combination index.
     * @param[out] arr array to set
     * @param index order of the combination
     * @param n number of array elements
     * @param mask first element in the array, must be multiple of 4
     */
    template<size_t SIZE>
    void setNComb4(array<uint16_t, SIZE> *arr, uint16_t index, uint16_t n,
        uint16_t mask) {
        auto end = n - 1;
        auto r = 4, fill = end;
        for (auto i = end; i >= 0; i--) {
            if (index >= choose(i, r)) {
                index -= choose(i, r--);
                (*arr)[i] = r | mask;
            } else {
                if ((fill & 0xc) == mask) {
                    fill -= 4;
                }
                (*arr)[i] = fill--;
            }
        }
    }

    /**
     * Check if specified permutation index represents a permutation
     * with an **odd** parity.
     * @param index the index to check
     * @param n element count in the permutation, n <= 16
     * @returns true if the parity is odd, false otherwise
     */
    bool getNParity(uint64_t index, uint16_t n);

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
