#include <iostream>
#include <stdexcept>
#include "UserInputPlayer.h"

UserInputPlayer::UserInputPlayer(Board::CellValue cellValue) :
    Player(cellValue) {
}

CellPosition
UserInputPlayer::computeNextMove(const Board& board) {
    char mark = getMark() == Board::CellValue::MarkX ? 'X' : 'O';
    std::cout << board.toString();

    for (; ;) {
        std::cout << "Player " << mark << " enter your move (row, col): ";
        std::string inputString;
        std::cin >> inputString;
        try {
            std::string::size_type pos = inputString.find(',');
            if (pos == std::string::npos)
                throw std::invalid_argument("Invalid format.");

            size_t row = atoi(inputString.substr(0, pos).c_str());
            size_t col = atoi(inputString.substr(pos + 1).c_str());
            if (board.getCellValue(row, col) != Board::Empty)
                throw std::invalid_argument("Cell is taken.");

            return CellPosition(row, col);
        }
        catch (const std::exception &ex) {
            std::cout << ex.what() << " Please re-enter.\n";
        }
    }
}
