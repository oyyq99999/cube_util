// Copyright 2019 Yunqi Ouyang
#ifndef CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_HPP_
#define CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_HPP_
#include<iostream>
#include<vector>
#include<string>

namespace cube_util {

    using std::ostream;
    using std::vector;
    using std::string;

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
    explicit Scramble(vector<uint16_t> moves);

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
}  // namespace cube_util

#endif  // CUBE_UTIL_INCLUDE_CUBE_UTIL_SCRAMBLE_HPP_
