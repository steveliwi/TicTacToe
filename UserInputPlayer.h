#pragma once

#include "Player.h"

// A player that requires user input.
class UserInputPlayer : public Player {
    public:
        UserInputPlayer(Board::CellValue cellValue);
        virtual CellPosition computeNextMove(const Board& board);
};
