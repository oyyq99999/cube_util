#include<cube_util/Scrambler222.hpp>
#include<cube_util/CubieCube222.hpp>
#include<cube_util/Cube222Solver.hpp>

namespace cube_util {

    Scrambler222::Scrambler222(): Scrambler222(N_MAX_LENGTH) {
    }

    Scrambler222::Scrambler222(uint16_t minScrambleLength): Scrambler(true) {
        minStateLength = 4;
        this->minScrambleLength = minScrambleLength;
    }
    string Scrambler222::scramble() {
        Cube222Solver s;
        do {
            s = Cube222Solver(CubieCube222::randomCube());
        } while (wcaCheck && s.isSolvableIn(minStateLength - 1));
        return s.generate(minScrambleLength);
    }
}
