#include <random>
#include <iostream>
#include <stdexcept>
#include "CellPosition.h"
#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(Board::CellValue cellValue, std::mt19937::result_type seed) :
    Player(cellValue),
    rng(seed) {
    char mark = getMark() == Board::CellValue::MarkX ? 'X' : 'O';
    std::cout << "Player " << mark << " seed " << seed << "\n";
}

CellPosition
RandomPlayer::computeNextMove(const Board& board) {
    std::vector<CellPosition> emptyList;
    for (size_t row=0; row<board.getBoardLength(); ++row) {
        for (size_t col=0; col<board.getBoardLength(); ++col) {
            if (board.getCellValue(row, col) == Board::CellValue::Empty) {
                emptyList.push_back(CellPosition(row,col));
            }
        }
    }

    if (emptyList.size() == 1)
        return emptyList.at(0);

    std::uniform_int_distribution<std::mt19937::result_type> dist(0, emptyList.size() - 1);
    size_t index = dist(rng);
    return emptyList.at(index);
}
