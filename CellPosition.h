#pragma once

#include <stdlib.h>

// Class for defining a cell position.
class CellPosition {
    public:
        size_t row, col;

    public:
        CellPosition(size_t _row, size_t _col) {
            row = _row;
            col = _col;
        }
};
