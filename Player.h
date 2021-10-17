#pragma once

#include "Board.h"

// Base class for defining a player.
class Player {
    private:
        Board::CellValue mark;
        
    public:
        Player(Board::CellValue _mark) {
            if ((_mark != Board::CellValue::MarkX) && (_mark != Board::CellValue::MarkO))
                throw std::invalid_argument("Player must be either X or O.");
            mark = _mark;
        }

        Board::CellValue getMark() const {
            return mark;
        }

    public:
        virtual CellPosition computeNextMove(const Board& board) = 0;
};

