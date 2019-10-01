// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLENNN_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLENNN_HPP_
#include<string>
#include<vector>
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
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLENNN_HPP_
