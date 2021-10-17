#pragma once

#include <iostream>
#include "Player.h"

// A player that requires user input.
class UserInputPlayer : public Player {
    public:
        UserInputPlayer(Board::CellValue cellValue) :
            Player(cellValue) {
        }

    public:
        virtual CellPosition computeNextMove(const Board& board) {
            char mark = getMark() == Board::CellValue::MarkX ? 'X' : 'O';
            for (; ;) {
                std::cout << board.toString() << "\n";
                std::cout << "Player " << mark << " enter your move (row, col): ";
                std::string inputString;
                std::cin >> inputString;

                std::string::size_type pos = inputString.find(',');
                if (pos == std::string::npos) {
                    std::cout << "Error: invalid format";
                    continue;
                }
                size_t row = atoi(inputString.substr(0, pos).c_str());
                size_t col = atoi(inputString.substr(pos + 1).c_str());
                return CellPosition(row, col);
            }
        }
};
