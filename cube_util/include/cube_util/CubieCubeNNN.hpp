#ifndef CUBIE_CUBE_NNN_HPP
#define CUBIE_CUBE_NNN_HPP
#include<array>
#include<cube_util/FaceletCubeNNN.hpp>
#include<cube_util/Utils.hpp>

namespace cube_util {

    using namespace constants;

    ////////////////////////////////////////////////////////////////////////////
    /// An abstract class representing common part of any NxNxN cube models by
    /// cubie level.
    /// It declares corner permutations in this order: `URF`, `UFL`, `ULB`,
    /// `UBR`, `DLF`, `DFR`, `DRB`, `DBL`. <br>
    /// It declares corner orientations in the same order with these numbers:
    /// - 0 means **oriented**;
    /// - 1 means **clockwise** twisted once from the **oriented** status;
    /// - 2 means **counter-clockwise** twisted.
    ////////////////////////////////////////////////////////////////////////////
    class CubieCubeNNN {

        /**
         * Outputs info about the cube, includes perms and twists
         */
        friend ostream& operator<<(ostream& os, const CubieCubeNNN &cc);

    protected:
        /** Permutations of the corners. */
        array<uint16_t, N_CORNER> cp;

        /** Orientations of the corners. */
        array<uint16_t, N_CORNER> co;

        /**
         * Set corner permutation state according to given index.
         * @param index specified index
         */
        virtual void setCP(uint16_t index);

        /**
         * Set corner orientation state according to given index.
         * @param index specified index
         */
        virtual void setCO(uint16_t);

    public:
        CubieCubeNNN();

        /**
         * Calculate corner permutation index of current state.
         */
        virtual uint16_t getCP() const;

        /**
         * Calculate corner orientation index of current state.
         */
        virtual uint16_t getCO() const;

        /**
         * Get a string representation of the cube state.
         * @returns a string describing the current state.
         */
        virtual string toString() const = 0;

        /**
         * Create a FaceletCubeNNN based on the CubieCubeNNN.
         * @returns a FaceletCubeNNN instance
         */
        virtual FaceletCubeNNN toFaceletCube() = 0;

        virtual ~CubieCubeNNN() = default;
    };
}

#endif // CUBIE_CUBE_NNN_HPP
