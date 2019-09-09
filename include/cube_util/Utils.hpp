#ifndef CUBE_UTIL_UTILS_HPP
#define CUBE_UTIL_UTILS_HPP
#include<string>

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
        const int Ux1 = 0;
        const int Ux2 = 1;
        const int Ux3 = 2;
        const int Rx1 = 3;
        const int Rx2 = 4;
        const int Rx3 = 5;
        const int Fx1 = 6;
        const int Fx2 = 7;
        const int Fx3 = 8;
    }

    namespace cube222 {
        const int N_MOVE = 9;
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
