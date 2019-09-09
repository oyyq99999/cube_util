#ifndef CUBIE_CUBE222_HPP
#define CUBIE_CUBE222_HPP
#include<iostream>
#include<array>
#include<cube_util/Utils.hpp>

using namespace std;

namespace cube_util {

    class CubieCube222 {

        array<uint16_t, constants::N_CORNERS> perm;
        array<uint16_t, constants::N_CORNERS> twist;
        friend ostream& operator<<(ostream& os, const CubieCube222 &cc);

        static const array<CubieCube222, cube_util::cube222::N_MOVE> MOVE_CUBES;
        static void cubeMult(CubieCube222 one, CubieCube222 another, CubieCube222 &result);

    public:
        CubieCube222();
        CubieCube222(array<uint16_t, constants::N_CORNERS> perm, array<uint16_t, constants::N_CORNERS> twist);
        void move(int move);
    };

}

#endif // CUBIE_CUBE222_HPP
