#pragma once

#include <random>
#include "Player.h"

// A player that makes random moves.
class RandomPlayer : public Player {
    public:
        RandomPlayer(Board::CellValue cellValue, std::mt19937::result_type seed);
        virtual CellPosition computeNextMove(const Board& board);

    private:
        std::mt19937 rng;
};
