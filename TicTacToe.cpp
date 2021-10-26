#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "Board.h"
#include "Player.h"
#include "UserInputPlayer.h"
#include "RandomPlayer.h"

int main() {
    Board board(3);

    std::unique_ptr<Player> playerX = std::make_unique<UserInputPlayer>(Board::CellValue::MarkX);
    std::unique_ptr<Player> playerO = std::make_unique<UserInputPlayer>(Board::CellValue::MarkO);

    // std::random_device dev;
    // std::mt19937::result_type seedX = dev();
    // std::mt19937::result_type seedO = dev();
    // std::unique_ptr<Player> playerX = std::make_unique<RandomPlayer>(Board::CellValue::MarkX, seedX);
    // std::unique_ptr<Player> playerO = std::make_unique<RandomPlayer>(Board::CellValue::MarkO, seedO);

    Player* currentPlayer = playerX.get();

    Board::Outcome outcome;
    for (; ;) {
        // check if the game is done
        outcome = board.evaluateOutcome();
        if (outcome != Board::Outcome::InProgress)
            break;

        // get player's next move
        CellPosition cellPosition = currentPlayer->computeNextMove(board);
        board.setCellValue(cellPosition, currentPlayer->getMark());

        // player takes turn
        currentPlayer = (currentPlayer == playerX.get()) ? playerO.get() : playerX.get();
    }

    // print board
    std::cout << board.toString();

    // print outcome
    const char* outcomeString;
    switch (outcome) {
        case Board::Outcome::PlayerXWon:
            outcomeString = "Player X won";
            break;
        case Board::Outcome::PlayerOWon:
            outcomeString = "Player O won";
            break;
        case Board::Outcome::Tied:
            outcomeString = "Tied";
            break;
    }
    std::cout << outcomeString;
}
