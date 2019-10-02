// Copyright 2019 Yunqi Ouyang
#include<cube_util/CubieCube333.hpp>
#include<sstream>

namespace cube_util {

    using std::invalid_argument;
    using std::ostringstream;
    using std::endl;

    using constants::N_FACE;

    using enums::CornerTwists::ORIENTED;
    using enums::CornerTwists::COUNTER_CLOCKWISE;

    using enums::Colors::U;
    using enums::Colors::D;

    using cube333::N_MOVE;
    using cube333::N_CORNER_PERM;
    using cube333::N_CORNER_TWIST;
    using cube333::N_EDGE_PERM;
    using cube333::N_EDGE_FLIP;
    using cube333::CORNER_FACELET_MAP;
    using cube333::EDGE_FACELET_MAP;
    using cube333::FACELET_PER_FACE;

    using cube333::Edges::UF;
    using cube333::Edges::UL;
    using cube333::Edges::UB;
    using cube333::Edges::UR;
    using cube333::Edges::DF;
    using cube333::Edges::DR;
    using cube333::Edges::DB;
    using cube333::Edges::DL;
    using cube333::Edges::FL;
    using cube333::Edges::BL;
    using cube333::Edges::BR;
    using cube333::Edges::FR;

    using cube333::EdgeFlips::NOT_FLIPPED;
    using cube333::EdgeFlips::FLIPPED;

    using utils::getNPerm;
    using utils::setNPerm;
    using utils::getNFlip;
    using utils::setNFlip;
    using utils::getNParity;
    using utils::randomizer;

    CubieCube333::CubieCube333():
        ep {UF, UL, UB, UR, DF, DR, DB, DL, FL, BL, BR, FR}, eo {NOT_FLIPPED} {}

    CubieCube333::CubieCube333(array<uint16_t, N_CORNER> cp,
        array<uint16_t, N_CORNER> co, array<uint16_t, N_EDGE> ep,
        array<uint16_t, N_EDGE> eo) {
        int twistsTotal = 0;
        int flipTotal = 0;
        uint16_t maskCorner = 0;
        uint16_t maskEdge = 0;

        for (auto i = 0; i < N_EDGE; i++) {
            if (ep[i] > FR || (maskEdge & (1 << ep[i])) != 0) {
                throw invalid_argument("invalid edge permutation!");
            }
            maskEdge |= 1 << ep[i];
            if ((eo[i] & 0xfffe) != 0) {
                throw invalid_argument("invalid edge orientation!");
            }
            flipTotal ^= eo[i];

            if (i < N_CORNER) {
                // (a & 0xfff8) != 0 is equivalent to a > 7 for uint16_t
                if ((cp[i] & 0xfff8) != 0 || (maskCorner & (1 << cp[i])) != 0) {
                    throw invalid_argument("invalid corner permutation!");
                }
                maskCorner |= 1 << cp[i];
                if (co[i] < ORIENTED || co[i] > COUNTER_CLOCKWISE) {
                    throw invalid_argument("invalid corner orientation!");
                }
                twistsTotal += co[i];
                this->cp[i] = cp[i];
                this->co[i] = co[i];
            }

            // assume all things are good, if we find something is wrong later,
            // we throw an exception
            this->ep[i] = ep[i];
            this->eo[i] = eo[i];
        }

        if ((flipTotal & 1) != 0) {
            throw invalid_argument("wrong edge orientation!");
        }

        if (twistsTotal % 3 != 0) {
            throw invalid_argument("wrong corner orientation!");
        }
    }

    CubieCube333::CubieCube333(uint16_t cp, uint16_t co,
        uint32_t ep, uint16_t eo) {
        if (cp >= N_CORNER_PERM || co >= N_CORNER_TWIST
            || ep >= N_EDGE_PERM || eo >= N_EDGE_FLIP) {
            throw invalid_argument("invalid parameters!");
        }
        this->setCP(cp);
        this->setCO(co);
        this->setEP(ep);
        this->setEO(eo);
    }

    void CubieCube333::setEP(uint32_t index) {
        setNPerm(&this->ep, index, N_EDGE);
    }

    void CubieCube333::setEO(uint16_t index) {
        setNFlip(&this->eo, index, N_EDGE);
    }

    void CubieCube333::move(uint16_t move) {
        move %= N_MOVE;
        cubeMult(*this, MOVE_CUBES[move], this);
    }

    uint32_t CubieCube333::getEP() const {
        return getNPerm(this->ep, N_EDGE);
    }

    uint16_t CubieCube333::getEO() const {
        return getNFlip(this->eo, N_EDGE);
    }

    void CubieCube333::cubeMult(CubieCube333 one, CubieCube333 another,
        CubieCube333 *result) {
        auto cp = array<uint16_t, N_CORNER>();
        auto co = array<uint16_t, N_CORNER>();
        auto ep = array<uint16_t, N_EDGE>();
        auto eo = array<uint16_t, N_EDGE>();
        for (auto i = 0; i < N_CORNER; i++) {
            cp[i] = one.cp[another.cp[i]];
            co[i] = (one.co[another.cp[i]] + another.co[i]) % 3;
        }
        for (auto i = 0; i < N_EDGE; i++) {
            ep[i] = one.ep[another.ep[i]];
            eo[i] = one.eo[another.ep[i]] ^ another.eo[i];
        }
        result->cp = cp;
        result->co = co;
        result->ep = ep;
        result->eo = eo;
    }

    FaceletCubeNNN CubieCube333::toFaceletCube() {
        auto f = vector<uint16_t>(N_FACE * FACELET_PER_FACE);
        for (auto i = 0; i < N_FACE; i++) {
            f[i * FACELET_PER_FACE + 4] = i;
        }
        for (auto i = 0; i < N_CORNER; i++) {
            auto piece = cp[i];
            auto orient = co[i];
            for (auto j = 0; j < 3; j++) {
                f[CORNER_FACELET_MAP[i][(j + orient) % 3]]
                    = CORNER_FACELET_MAP[piece][j] / FACELET_PER_FACE;
            }
        }
        for (auto i = 0; i < N_EDGE; i++) {
            auto piece = ep[i];
            auto orient = eo[i];
            for (auto j = 0; j < 2; j++) {
                f[EDGE_FACELET_MAP[i][(j + orient) & 1]]
                    = EDGE_FACELET_MAP[piece][j] / FACELET_PER_FACE;
            }
        }
        return FaceletCubeNNN(3, f);
    }

    CubieCube333 CubieCube333::fromFaceletCube(FaceletCubeNNN fc) {
        if (fc.getSize() != 3) {
            throw invalid_argument("needs a 3x3x3 cube!");
        }
        auto f = fc.getFacelets();
        array<uint16_t, N_CORNER> cp;
        array<uint16_t, N_CORNER> co;
        array<uint16_t, N_EDGE> ep;
        array<uint16_t, N_EDGE> eo;
        uint16_t color1, color2, ori;
        for (auto i = 0; i < N_CORNER; i++) {
            for (ori = 0; ori < 3; ori++) {
                if (f[CORNER_FACELET_MAP[i][ori]] == U
                    || f[CORNER_FACELET_MAP[i][ori]] == D) {
                    break;
                }
            }
            color1 = f[CORNER_FACELET_MAP[i][(ori + 1) % 3]];
            color2 = f[CORNER_FACELET_MAP[i][(ori + 2) % 3]];
            for (auto j = 0; j < N_CORNER; j++) {
                if (color1 == CORNER_FACELET_MAP[j][1] / FACELET_PER_FACE
                    && color2 == CORNER_FACELET_MAP[j][2] / FACELET_PER_FACE) {
                    cp[i] = j;
                    co[i] = ori;
                    break;
                }
            }
        }

        for (auto i = 0; i < N_EDGE; i++) {
            for (auto j = 0; j < N_EDGE; j++) {
                if (f[EDGE_FACELET_MAP[i][0]]
                    == EDGE_FACELET_MAP[j][0] / FACELET_PER_FACE
                    && f[EDGE_FACELET_MAP[i][1]]
                    == EDGE_FACELET_MAP[j][1] / FACELET_PER_FACE) {
                    ep[i] = j;
                    eo[i] = NOT_FLIPPED;
                }
                if (f[EDGE_FACELET_MAP[i][0]]
                    == EDGE_FACELET_MAP[j][1] / FACELET_PER_FACE
                    && f[EDGE_FACELET_MAP[i][1]]
                    == EDGE_FACELET_MAP[j][0] / FACELET_PER_FACE) {
                    ep[i] = j;
                    eo[i] = FLIPPED;
                }
            }
        }
        return CubieCube333(cp, co, ep, eo);
    }

    bool CubieCube333::isSolvable(uint16_t cpi, uint32_t epi) {
        uint16_t parity = getNParity(cpi, N_CORNER);
        parity ^= getNParity(epi, N_EDGE);
        return parity == 0;
    }

    CubieCube333 CubieCube333::randomCube() {
        auto rcp = randomizer(0, N_CORNER_PERM - 1);
        auto rep = randomizer(0, N_EDGE_PERM - 1);
        uint16_t cp;
        uint32_t ep;
        do {
            cp = rcp();
            ep = rep();
        } while (!isSolvable(cp, ep));
        auto r = randomizer(0, N_EDGE_FLIP * N_CORNER_TWIST - 1);
        auto orient = r();
        return CubieCube333(cp, orient % N_CORNER_TWIST,
            ep, orient / N_CORNER_TWIST);
    }

    string CubieCube333::toString() const {
        ostringstream os;
        os << "Corner Perms:";
        for (auto i = 0; i < N_CORNER; i++) {
            os << " " << cp[i];
        }
        os << endl << "Corner Twists:";
        for (auto i = 0; i < N_CORNER; i++) {
            os << " " << co[i];
        }
        os << endl << "Edge Perms:";
        for (auto i = 0; i < N_EDGE; i++) {
            os << " " << ep[i];
        }
        os << endl << "Edge Flips:";
        for (auto i = 0; i < N_EDGE; i++) {
            os << " " << eo[i];
        }
        os << endl;
        return os.str();
    }

}  // namespace cube_util
