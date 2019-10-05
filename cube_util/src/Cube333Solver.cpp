// Copyright 2019 Yunqi Ouyang
#include<cube_util/Cube333Solver.hpp>
#include<cube_util/MoveSequenceNNN.hpp>

namespace cube_util {

    using std::make_unique;
    using std::max;
    using std::min;
    using std::fill;
    using std::to_string;
    using std::invalid_argument;
    using std::runtime_error;

    using cube333::N_MAX_PHASE1_LENGTH;
    using cube333::N_MAX_PHASE2_LENGTH;
    using cube333::N_MAX_CHECK_LENGTH;
    using cube333::N_EDGE_FLIP;
    using cube333::N_CORNER_TWIST;
    using cube333::N_SLICE_POSITION;
    using cube333::N_CORNER_PERM;
    using cube333::N_SLICE_EDGE_PERM;
    using cube333::N_UD8EDGE_PERM;
    using cube333::SOLVED_CP;
    using cube333::SOLVED_FLIP;
    using cube333::SOLVED_SLICE_POSITION;
    using cube333::SOLVED_TWIST;
    using cube333::SOLVED_UD8_EP;
    using cube333::SOLVED_SLICE_EP;
    using cube333::N_PHASE2_MOVE_COUNT;
    using cube333::PHASE2_MOVE;

    using constants::N_AXIS;
    using constants::N_MOVE_PER_AXIS;
    using constants::INVALID_AXIS;

    using utils::setPruning;
    using utils::getPruning;
    using utils::reverseMove;

    Cube333Solver::Cube333Solver(CubieCube333 c) {
        cc = c;
    }

    int16_t Cube333Solver::getSolutionLength() const {
        return solutionLength;
    }

    /**
     * Iterating search function.
     * Try each depth to search for a solution.
     * @param maxLength how many moves in total is acceptable
     * @returns whether the cube is solved
     */
    bool Cube333Solver::_solve(uint16_t maxLength) {
        // already solved and fulfills requirement
        if (solutionLength >= 0 && solutionLength <= maxLength) {
            return true;
        }

        phase1Length = -1;
        solutionLength = -1;
        auto co = cc.getCOIndex();
        auto eo = cc.getEOIndex();
        auto slice = cc.getSlicePositionIndex();

        auto upperBound = min(maxLength, N_MAX_PHASE1_LENGTH);
        for (auto i = 0; i <= upperBound; i++) {
            if (phase1(co, eo, slice, i, INVALID_AXIS, 0, maxLength, false)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Phase1 searching function.
     * @param co corner orientation index to solve
     * @param eo edge orientation index to solve
     * @param slice E-slice edges positions index to solve
     * @param moveCount move count used to solve
     * @param lastAxis axis of last move
     * @param depth current search depth
     * @param maxLength how many moves in total is acceptable (including phase2)
     * @param checkOnly whether to check the cube is solvable only
     * @returns whether the cube is solved
     */
    bool Cube333Solver::phase1(uint16_t co, uint16_t eo, uint16_t slice,
        uint16_t moveCount, uint16_t lastAxis, uint16_t depth,
        uint16_t maxLength, bool checkOnly) {
        if (moveCount == 0) {
            if (co == SOLVED_CP && eo == SOLVED_FLIP &&
                slice == SOLVED_SLICE_POSITION) {
                if (checkOnly) {
                    auto c = CubieCube333(cc);
                    for (auto i = 0; i < depth; i++) {
                        c.move(solution[i]);
                    }
                    return c == CubieCube333();
                }
                // phase1 solved
                phase1Length = depth;
                return initPhase2(lastAxis, depth, maxLength);
            }
            return false;
        }
        for (auto axis = 0; axis < N_AXIS; axis++) {
            // we assume URF always show before DLB respectively
            if (axis != lastAxis && axis + 3 != lastAxis) {
                for (auto power = 0; power < N_MOVE_PER_AXIS; power++) {
                    auto move = axis * N_MOVE_PER_AXIS + power;

                    auto newCO = CubieCube333::getTwistMove(co, move);
                    auto newEO = CubieCube333::getFlipMove(eo, move);
                    auto newSlice =
                        CubieCube333::getSlicePositionMove(slice, move);

                    auto pruningValue = max(
                        getTwistSlicePruning(newCO, newSlice),
                        getFlipSlicePruning(newEO, newSlice));

                    // if the new state needs more than moveCount to solve,
                    // it means any new state generated by the same axis
                    // needs at least moveCount moves to solve, which is not
                    // solvable in moveCount - 1 moves, so we can skip them.
                    if (pruningValue > moveCount) {
                        break;
                    } else if (pruningValue == moveCount) {
                        continue;
                    }

                    solution[depth] = move;
                    if (phase1(newCO, newEO, newSlice, moveCount - 1, axis,
                        depth + 1, maxLength, checkOnly)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * Initializing phase2.
     * @param lastAxis lastAxis of phase1, or a big number indicating last move
     * doesn't exist
     * @param depth current search depth (including phase1)
     * @param maxLength how many moves in total is acceptable (including phase1)
     * @returns whether the cube is solved
     */
    bool Cube333Solver::initPhase2(uint16_t lastAxis, uint16_t depth,
        uint16_t maxLength) {
        auto c = CubieCube333(cc);
        for (auto i = 0; i < depth; i++) {
            c.move(solution[i]);
        }

        auto cp = c.getCPIndex();
        auto ud8EP = c.getUD8EPIndex();
        auto sliceEP = c.getSliceEPIndex();

        // we wouldn't try any phase1 ends with phase2 moves unless
        // it's already totally solved
        if (depth > 0) {
            auto lastMove = solution[depth - 1];
            for (auto i = 0; i < N_PHASE2_MOVE_COUNT; i++) {
                if (lastMove == PHASE2_MOVE[i]) {
                    if ((cp != SOLVED_CP || ud8EP != SOLVED_UD8_EP ||
                        sliceEP != SOLVED_SLICE_EP)) {
                        return false;
                    }
                    break;
                }
            }
        }

        auto upperBound = min(uint16_t(maxLength - depth), N_MAX_PHASE2_LENGTH);
        for (auto i = 0; i <= upperBound; i++) {
            if (phase2(cp, ud8EP, sliceEP, i, lastAxis, depth)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Phase2 searching function.
     * @param cp corner permutation index to solve
     * @param ud8EP UD 8 edges permutation index to solve
     * @param sliceEP E-slice edges permutation index to solve
     * @param moveCount move count used to solve
     * @param lastAxis axis of last move
     * @param depth current search depth
     * @returns whether the cube is solved
     */
    bool Cube333Solver::phase2(uint16_t cp, uint16_t ud8EP, uint16_t sliceEP,
        uint16_t moveCount, uint16_t lastAxis, uint16_t depth) {
        if (moveCount == 0) {
            if (cp == SOLVED_CP && ud8EP == SOLVED_UD8_EP &&
                sliceEP == SOLVED_SLICE_EP) {
                solutionLength = depth;
                return true;
            }
            return false;
        }
        for (auto i = 0; i < N_PHASE2_MOVE_COUNT; i++) {
            auto move = PHASE2_MOVE[i];
            auto axis = move / N_MOVE_PER_AXIS;
            // we assume URF always show before DLB respectively
            if (axis != lastAxis && axis + 3 != lastAxis) {
                auto newCP = CubieCube333::getCPMove(cp, i);
                auto newUD8EP = CubieCube333::getUD8EPMove(ud8EP, i);
                auto newSliceEP = CubieCube333::getSliceEPMove(sliceEP, i);

                auto pruningValue = max(
                    getCPSliceEPPruning(newCP, newSliceEP),
                    getUD8EPSliceEPPruning(newUD8EP, newSliceEP));

                // since we are not iterating moves by axis here, we can not
                // utilize the same trick in phase1 elegantly here,
                // but it's still doable.
                if (pruningValue >= moveCount) {
                    continue;
                }

                solution[depth] = move;
                if (phase2(newCP, newUD8EP, newSliceEP, moveCount - 1, axis,
                    depth + 1)) {
                    return true;
                }
            }
        }
        return false;
    }

    unique_ptr<MoveSequence> Cube333Solver::solve() {
        return this->solve(N_MAX_LENGTH);
    }

    unique_ptr<MoveSequence> Cube333Solver::solve(uint16_t maxLength) {
        if (!this->_solve(maxLength)) {
            throw runtime_error("not solved!");
        }
        vector<uint16_t> moves;
        for (auto i = 0; i < this->solutionLength; i++) {
            moves.push_back(solution[i]);
        }
        return make_unique<MoveSequenceNNN>(3, moves);
    }

    unique_ptr<MoveSequence> Cube333Solver::generate() {
        return this->generate(N_MAX_LENGTH);
    }

    unique_ptr<MoveSequence> Cube333Solver::generate(uint16_t maxLength) {
        if (!this->_solve(maxLength)) {
            throw runtime_error("not solved!");
        }
        vector<uint16_t> moves;
        for (auto i = this->solutionLength - 1; i >= 0; i--) {
            moves.push_back(reverseMove(solution[i]));
        }
        return make_unique<MoveSequenceNNN>(3, moves);
    }

    bool Cube333Solver::isSolvableIn(uint16_t maxLength) {
        if (maxLength > N_MAX_CHECK_LENGTH) {
            throw invalid_argument("max check length is " +
                to_string(N_MAX_CHECK_LENGTH));
        }
        if (solutionLength >= 0 && solutionLength <= maxLength) {
            return true;
        }

        auto coIndex = cc.getCOIndex();
        auto eoIndex = cc.getEOIndex();
        auto slicePositionIndex = cc.getSlicePositionIndex();

        auto lowerBound = max(getTwistSlicePruning(coIndex, slicePositionIndex),
            getFlipSlicePruning(eoIndex, slicePositionIndex));
        auto upperBound = maxLength;
        for (auto i = lowerBound; i <= upperBound; i++) {
            if (phase1(coIndex, eoIndex, slicePositionIndex, i, INVALID_AXIS,
                0, maxLength, true)) {
                return true;
            }
        }
        return false;
    }

    uint16_t Cube333Solver::getFlipSlicePruning(uint16_t flip, uint16_t slice) {
        static auto pruningTable = [] {
            const uint32_t totalCount = N_EDGE_FLIP * N_SLICE_POSITION;
            auto ret = array<uint16_t, ((totalCount + 3) >> 2)>();
            fill(ret.begin(), ret.end(), 0xffff);
            uint32_t count = 0;
            for (auto depth = 0; count < totalCount; depth++) {
                if (depth == 0) {
                    setPruning(&ret,
                        SOLVED_FLIP * N_SLICE_POSITION + SOLVED_SLICE_POSITION,
                        depth);
                    count++;
                    continue;
                }
                for (auto flip = 0; flip < N_EDGE_FLIP; flip++) {
                    for (auto slice = 0; slice < N_SLICE_POSITION; slice++) {
                        auto index = flip * N_SLICE_POSITION + slice;
                        if (getPruning(ret, index) == depth - 1) {
                            for (auto move = 0; move < N_MOVE; move++) {
                                auto newFlip =
                                    CubieCube333::getFlipMove(flip, move);
                                auto newSlice =
                                    CubieCube333::getSlicePositionMove(
                                        slice, move);
                                auto newIndex =
                                    newFlip * N_SLICE_POSITION + newSlice;
                                if (getPruning(ret, newIndex) == 0xf) {
                                    setPruning(&ret, newIndex, depth);
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return ret;
        }();
        return getPruning(pruningTable, flip * N_SLICE_POSITION + slice);
    }

    uint16_t
    Cube333Solver::getTwistSlicePruning(uint16_t twist, uint16_t slice) {
        static auto pruningTable = [] {
            const uint32_t totalCount = N_CORNER_TWIST * N_SLICE_POSITION;
            auto ret = array<uint16_t, ((totalCount + 3) >> 2)>();
            fill(ret.begin(), ret.end(), 0xffff);
            uint32_t count = 0;
            for (auto depth = 0; count < totalCount; depth++) {
                if (depth == 0) {
                    setPruning(&ret,
                        SOLVED_TWIST * N_SLICE_POSITION + SOLVED_SLICE_POSITION,
                        depth);
                    count++;
                    continue;
                }
                for (auto twist = 0; twist < N_CORNER_TWIST; twist++) {
                    for (auto slice = 0; slice < N_SLICE_POSITION; slice++) {
                        auto index = twist * N_SLICE_POSITION + slice;
                        if (getPruning(ret, index) == depth - 1) {
                            for (auto move = 0; move < N_MOVE; move++) {
                                auto newTwist =
                                    CubieCube333::getTwistMove(twist, move);
                                auto newSlice =
                                    CubieCube333::getSlicePositionMove(
                                        slice, move);
                                auto newIndex =
                                    newTwist * N_SLICE_POSITION + newSlice;
                                if (getPruning(ret, newIndex) == 0xf) {
                                    setPruning(&ret, newIndex, depth);
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return ret;
        }();
        return getPruning(pruningTable, twist * N_SLICE_POSITION + slice);
    }

    uint16_t
    Cube333Solver::getCPSliceEPPruning(uint16_t cp, uint16_t sliceEP) {
        static auto pruningTable = [] {
            const uint32_t totalCount = N_CORNER_PERM * N_SLICE_EDGE_PERM;
            auto ret = array<uint16_t, ((totalCount + 3) >> 2)>();
            fill(ret.begin(), ret.end(), 0xffff);
            uint32_t count = 0;
            for (auto depth = 0; count < totalCount; depth++) {
                if (depth == 0) {
                    setPruning(&ret,
                        SOLVED_CP * N_SLICE_EDGE_PERM + SOLVED_SLICE_EP, depth);
                    count++;
                    continue;
                }
                for (auto cp = 0; cp < N_CORNER_PERM; cp++) {
                    for (auto sliceEP = 0; sliceEP < N_SLICE_EDGE_PERM;
                        sliceEP++) {
                        auto index = cp * N_SLICE_EDGE_PERM + sliceEP;
                        if (getPruning(ret, index) == depth - 1) {
                            for (auto i = 0; i < N_PHASE2_MOVE_COUNT; i++) {
                                auto newCP =
                                    CubieCube333::getCPMove(cp, i);
                                auto newSliceEP =
                                    CubieCube333::getSliceEPMove(sliceEP, i);
                                auto newIndex =
                                    newCP * N_SLICE_EDGE_PERM + newSliceEP;
                                if (getPruning(ret, newIndex) == 0xf) {
                                    setPruning(&ret, newIndex, depth);
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return ret;
        }();
        return getPruning(pruningTable, cp * N_SLICE_EDGE_PERM + sliceEP);
    }

    uint16_t
    Cube333Solver::getUD8EPSliceEPPruning(uint16_t ud8EP, uint16_t sliceEP) {
        static auto pruningTable = [] {
            const uint32_t totalCount = N_UD8EDGE_PERM * N_SLICE_EDGE_PERM;
            auto ret = array<uint16_t, ((totalCount + 3) >> 2)>();
            fill(ret.begin(), ret.end(), 0xffff);
            uint32_t count = 0;
            for (auto depth = 0; count < totalCount; depth++) {
                if (depth == 0) {
                    setPruning(&ret,
                        SOLVED_UD8_EP * N_SLICE_EDGE_PERM + SOLVED_SLICE_EP,
                        depth);
                    count++;
                    continue;
                }
                for (auto ud8EP = 0; ud8EP < N_UD8EDGE_PERM; ud8EP++) {
                    for (auto sliceEP = 0; sliceEP < N_SLICE_EDGE_PERM;
                        sliceEP++) {
                        auto index = ud8EP * N_SLICE_EDGE_PERM + sliceEP;
                        if (getPruning(ret, index) == depth - 1) {
                            for (auto i = 0; i < N_PHASE2_MOVE_COUNT; i++) {
                                auto newUD8EP =
                                    CubieCube333::getUD8EPMove(ud8EP, i);
                                auto newSliceEP =
                                    CubieCube333::getSliceEPMove(sliceEP, i);
                                auto newIndex =
                                    newUD8EP * N_SLICE_EDGE_PERM + newSliceEP;
                                if (getPruning(ret, newIndex) == 0xf) {
                                    setPruning(&ret, newIndex, depth);
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return ret;
        }();
        return getPruning(pruningTable, ud8EP * N_SLICE_EDGE_PERM + sliceEP);
    }
}  // namespace cube_util
