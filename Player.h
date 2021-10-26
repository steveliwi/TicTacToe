#pragma once

#include "Board.h"

// Base class for defining a player.
class Player {
    private:
        Board::CellValue mark;
        
    public:
        Player(Board::CellValue _mark);
        Board::CellValue getMark() const;

    public:
        virtual CellPosition computeNextMove(const Board& board) = 0;
};
