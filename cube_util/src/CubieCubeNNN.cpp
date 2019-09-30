#include<cube_util/CubieCubeNNN.hpp>

namespace cube_util {

    using namespace utils;
    using namespace enums;

    CubieCubeNNN::CubieCubeNNN():
        cp {URF, UFL, ULB, UBR, DLF, DFR, DRB, DBL},
        co {ORIENTED} {
    }

    void CubieCubeNNN::setCP(uint16_t index) {
        setNPerm(this->cp, index, N_CORNER);
    }

    void CubieCubeNNN::setCO(uint16_t index) {
        setNTwist(this->co, index, N_CORNER);
    }

    uint16_t CubieCubeNNN::getCP() const {
        return getNPerm(this->cp, N_CORNER);
    }

    uint16_t CubieCubeNNN::getCO() const {
        return getNTwist(this->co, N_CORNER);
    }

    ostream& operator<<(ostream &os, const CubieCubeNNN &cc) {
        return os << cc.toString();
    }
}
