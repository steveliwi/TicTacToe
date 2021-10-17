#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

class CellPosition {
    public:
        size_t row, col;

    public:
        CellPosition(size_t _row, size_t _col) {
            row = _row;
            col = _col;
        }
};

// Class for maintaining every cells in the board, and evaluating the state of the game (e.g. if game is finished).
class Board {
    public:
        enum CellValue { Empty, MarkX, MarkO };
        enum Outcome { InProgress, PlayerXWon, PlayerOWon, Tied };

    private:
        std::vector<std::vector<CellValue>> cells;

    public:
        Board(size_t boardLength) {
            cells.resize(boardLength, std::vector<CellValue>(boardLength, Empty));
        }

        size_t getBoardLength() const {
            return cells.size();
        }

        void setCellValue(size_t row, size_t col, CellValue cellValue) {
            if (getCellValue(row, col) != Empty)
                throw std::invalid_argument("Cell has been taken.");
            cells.at(row).at(col) = cellValue;
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
            // TODO: check for connecting rows
            // TODO: check for connecting columns
            // TODO: check diagonals
            return Outcome::InProgress;
        }

    private:
        void validateCellPosition(size_t row, size_t col) const {
            if (row < 0 || row >= cells.size())
                throw std::out_of_range("Invalid row.");
            if (col < 0 || col >= cells.size())
                throw std::out_of_range("Invalid column.");
        }
};

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

class SillyPlayer : public Player {
    public:
        SillyPlayer(Board::CellValue cellValue) :
            Player(cellValue) {
        }

    public:
        virtual CellPosition computeNextMove(const Board& board) {
            return CellPosition(0, 0);
        }
};

int main() {
    Board board(3);

    std::unique_ptr<Player> playerX = std::make_unique<SillyPlayer>(Board::CellValue::MarkX);
    std::unique_ptr<Player> playerO = std::make_unique<SillyPlayer>(Board::CellValue::MarkO);

    Player* currentPlayer = playerX.get();

    Board::Outcome outcome;
    for (; ;) {
        outcome = board.evaluateOutcome();
        if (outcome != Board::Outcome::InProgress)
            break;
        CellPosition cellPosition = currentPlayer->computeNextMove(board);
        board.setCellValue(cellPosition, currentPlayer->getMark());
        currentPlayer = (currentPlayer == playerX.get()) ? playerO.get() : playerX.get();
    }

    // print outcome
}
