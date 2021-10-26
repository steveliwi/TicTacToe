#pragma once

#include <vector>
#include "CellPosition.h"

// Class for maintaining every cells in the board, and evaluating the state of the game (e.g. if game is finished).
class Board {
    public:
        enum CellValue { Empty, MarkX, MarkO };
        enum Outcome { InProgress, PlayerXWon, PlayerOWon, Tied };

    private:
        std::vector<std::vector<CellValue>> cells;
        size_t numberOfEmptyCells;

    public:
        Board(size_t boardLength);

        size_t getBoardLength() const;
        size_t getNumberOfEmptyCells() const;

        void setCellValue(size_t row, size_t col, CellValue cellValue);
        CellValue getCellValue(size_t row, size_t col) const;

        void setCellValue(const CellPosition& cellPosition, CellValue cellValue);
        CellValue getCellValue(const CellPosition& cellPosition) const;

        void validateCellPosition(size_t row, size_t col) const;
        Outcome evaluateOutcome() const;

        std::string toString() const;

};
