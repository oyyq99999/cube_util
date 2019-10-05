// Copyright 2019 Yunqi Ouyang
#include<cube_util/CubieCubeNNN.hpp>

namespace cube_util {

    using std::ostream;

    using utils::setNPerm;
    using utils::getNPerm;
    using utils::setNTwist;
    using utils::getNTwist;

    using enums::Corners::URF;
    using enums::Corners::UFL;
    using enums::Corners::ULB;
    using enums::Corners::UBR;
    using enums::Corners::DLF;
    using enums::Corners::DFR;
    using enums::Corners::DRB;
    using enums::Corners::DBL;

    using enums::CornerTwists::ORIENTED;

    CubieCubeNNN::CubieCubeNNN():
        cp {URF, UFL, ULB, UBR, DLF, DFR, DRB, DBL},
        co {ORIENTED} {}

    void CubieCubeNNN::setCP(uint16_t index) {
        setNPerm(&cp, index, N_CORNER);
    }

    void CubieCubeNNN::setCO(uint16_t index) {
        setNTwist(&co, index, N_CORNER);
    }

    uint16_t CubieCubeNNN::getCPIndex() const {
        return getNPerm(cp, N_CORNER);
    }

    uint16_t CubieCubeNNN::getCOIndex() const {
        return getNTwist(co, N_CORNER);
    }

    ostream& operator<<(ostream &os, const CubieCubeNNN &cc) {
        return os << cc.toString();
    }
}  // namespace cube_util
