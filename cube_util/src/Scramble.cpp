// Copyright 2019 Yunqi Ouyang
#include<cube_util/Scramble.hpp>

namespace cube_util {

    Scramble::Scramble(const vector<uint16_t> moves): moveSequence(moves) {
        length = moveSequence.size();
    }

    vector<uint16_t> Scramble::getMoves() const {
        return this->moveSequence;
    }

    uint16_t Scramble::getLength() const {
        return this->length;
    }

    ostream& operator<<(ostream& os, const Scramble &s) {
        return os << s.toString();
    }
}  // namespace cube_util
