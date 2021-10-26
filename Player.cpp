#include <stdexcept>
#include "Player.h"

Player::Player(Board::CellValue _mark) {
    if ((_mark != Board::CellValue::MarkX) && (_mark != Board::CellValue::MarkO))
        throw std::invalid_argument("Player must be either X or O.");
    mark = _mark;
}

Board::CellValue
Player::getMark() const {
    return mark;
}
