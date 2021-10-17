#pragma once

#include <vector>
#include <stdexcept>
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
        Board(size_t boardLength) {
            cells.resize(boardLength, std::vector<CellValue>(boardLength, Empty));
            numberOfEmptyCells = boardLength * boardLength;
        }

        size_t getBoardLength() const {
            return cells.size();
        }

        void setCellValue(size_t row, size_t col, CellValue cellValue) {
            if (getCellValue(row, col) != Empty)
                throw std::invalid_argument("Cell has been taken.");
            cells.at(row).at(col) = cellValue;
            --numberOfEmptyCells;
        }

        CellValue getCellValue(size_t row, size_t col) const {
            validateCellPosition(row, col);
            return cells.at(row).at(col);
        }

        void setCellValue(const CellPosition& cellPosition, CellValue cellValue) {
            return setCellValue(cellPosition.row, cellPosition.col, cellValue);
        }

        CellValue getCellValue(const CellPosition& cellPosition) const {
            return getCellValue(cellPosition.row, cellPosition.col);
        }

        Outcome evaluateOutcome() const {
            // check for connecting rows
            for (size_t row=0; row<cells.size(); ++row) {
                CellValue cellValue = getCellValue(row, 0);
                if (cellValue != Empty) {
                    bool isConnected = true;
                    for (size_t col=1; col<cells.size(); ++col) {
                        if (getCellValue(row, col) != cellValue) {
                            isConnected = false;
                            break;
                        }
                    }
                    if (isConnected) {
                        return (cellValue == MarkX) ? PlayerXWon : PlayerOWon;
                    }
                }
            }

            // check for connecting columns
            for (size_t col=0; col<cells.size(); ++col) {
                CellValue cellValue = getCellValue(0, col);
                if (cellValue != Empty) {
                    bool isConnected = true;
                    for (size_t row=1; row<cells.size(); ++row) {
                        if (getCellValue(row, col) != cellValue) {
                            isConnected = false;
                            break;
                        }
                    }
                    if (isConnected) {
                        return (cellValue == MarkX) ? PlayerXWon : PlayerOWon;
                    }
                }
            }

            // check diagonals
            CellValue cellValue = getCellValue(0, 0);
            if (cellValue != Empty) {
                bool isConnected = true;
                for (size_t n=1; n<cells.size(); ++n) {
                    if (getCellValue(n, n) != cellValue) {
                        isConnected = false;
                        break;
                    }
                }
                if (isConnected) {
                    return (cellValue == MarkX) ? PlayerXWon : PlayerOWon;
                }
            }
            size_t row = cells.size() - 1;
            size_t col = 0;
            cellValue = getCellValue(row--, col++);
            if (cellValue != Empty) {
                bool isConnected = true;
                for (; col<cells.size(); --row, ++col) {
                    if (getCellValue(row, col) != cellValue) {
                        isConnected = false;
                        break;
                    }
                }
                if (isConnected) {
                    return (cellValue == MarkX) ? PlayerXWon : PlayerOWon;
                }
            }

            // check if all cells are taken
            if (numberOfEmptyCells == 0)
                return Tied;

            return Outcome::InProgress;
        }

    std::string toString() const {
        std::ostringstream ss;
        for (size_t row=0; row<getBoardLength(); ++row) {
            for (size_t col=0; col<getBoardLength(); ++col) {
                char c {};
                switch (getCellValue(row, col)) {
                    case CellValue::Empty:
                        c = '-';
                        break;
                    case CellValue::MarkX:
                        c = 'X';
                        break;
                    case CellValue::MarkO:
                        c = 'O';
                        break;
                }
                ss << c;
            }
            ss << '\n';
        }
        return ss.str();
    }

    private:
        void validateCellPosition(size_t row, size_t col) const {
            if (row < 0 || row >= cells.size())
                throw std::out_of_range("Invalid row.");
            if (col < 0 || col >= cells.size())
                throw std::out_of_range("Invalid column.");
        }
};
