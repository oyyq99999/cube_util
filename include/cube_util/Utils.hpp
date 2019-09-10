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
        const int N_CORNERS = 8;

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
