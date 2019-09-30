#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP
#include<string>

using namespace std;

namespace cube_util {

    ////////////////////////////////////////////////////////////////////////////
    /// A general cube scrambler interface which is able to give
    /// WCA-compatible scrambles.
    ////////////////////////////////////////////////////////////////////////////
    class Scrambler {

    protected:
        /** Whether to check the scramble state to satisfy WCA regulations */
        bool wcaCheck = true;

        /** WCA scramble state requirement */
        uint16_t minStateLength = 2;

        /// Lower limit of the scramble sequence length, which is useful
        /// for small cubes
        uint16_t minScrambleLength = 0;

    public:

        /**
         * Constructor of the class.
         * @param wcaCheck whether check for WCA state requirements
         */
        Scrambler(bool wcaCheck);

        /**
         * The scramble function. This generates a new scramble on each call.
         * @returns the scramble sequence
         */
        virtual string scramble() = 0;

        virtual ~Scrambler() = default;
    };
}

#endif // SCRAMBLER_HPP
