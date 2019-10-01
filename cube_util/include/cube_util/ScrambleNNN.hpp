#ifndef SCRAMBLE_NNN_HPP
#define SCRAMBLE_NNN_HPP
#include<cube_util/Scramble.hpp>

namespace cube_util {

    ////////////////////////////////////////////////////////////////////////////
    /// A class representing a scramble object for an NxNxN cube.
    ////////////////////////////////////////////////////////////////////////////
    class ScrambleNNN : public Scramble {
        /** The cube size */
        uint16_t size;
    public:
        /**
         * Constructor of the class.
         * @param size size of the cube
         * @param s the scramble string to parse from
         */
        ScrambleNNN(uint16_t size, string s);

        string toString() const override;

        /**
         * Parse a scramble string to number format.
         * @param s the scramble string to parse from
         * @returns the parsed scramble sequence
         */
        static vector<uint16_t> parse(string s);
    };
}

#endif // SCRAMBLE_NNN_HPP
