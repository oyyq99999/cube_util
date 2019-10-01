#ifndef SCRAMBLE_HPP
#define SCRAMBLE_HPP
#include<iostream>
#include<vector>

using namespace std;

namespace cube_util {

    ////////////////////////////////////////////////////////////////////////////
    /// A class representing a scramble object, which contains scramble
    /// sequence in numbers and length, and can be converted to string.
    ////////////////////////////////////////////////////////////////////////////
    class Scramble {
        /**
         * Outputs the scramble
         */
        friend ostream& operator<<(ostream& os, const Scramble &s);
    protected:
        /** Move sequence in numbers */
        vector<uint16_t> moveSequence;

        /** Scramble length */
        uint16_t length;

        /**
         * Constructor of the class.
         * @param moves move sequence in numbers
         */
        Scramble(vector<uint16_t> moves);
    public:
        /**
         * Get move sequence in numbers.
         * @returns move sequence in numbers
         */
        vector<uint16_t> getMoves() const;

        /**
         * Get scramble length.
         * @returns scramble length
         */
        uint16_t getLength() const;

        /**
         * Get the scramble in humban-readable format.
         * @returns the scramble string
         */
        virtual string toString() const = 0;

        virtual ~Scramble() = default;
    };
}

#endif // SCRAMBLE_HPP
