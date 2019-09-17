#ifndef SCRAMBLER222_HPP
#define SCRAMBLER222_HPP
#include<cstdint>
#include<cube_util/Scrambler.hpp>

namespace cube_util {

    ////////////////////////////////////////////////////////////////////////////
    /// A 2x2x2 cube scrambler which is able to give WCA-compatible scrambles.
    ////////////////////////////////////////////////////////////////////////////
    class Scrambler222 : public Scrambler {
    public:
        /**
         * The default constructor.
         */
        Scrambler222();

        /**
         * Constructor of the class.
         * @param minScrambleLength lower limit of the scramble sequence
         * length
         */
        Scrambler222(uint16_t minScrambleLength);

        string scramble() override;
    };
}

#endif // SCRAMBLER222_HPP
