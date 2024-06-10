#pragma once

struct Cell {
    int row;
    int column;

    bool operator==(const Cell& other) const {
        return row == other.row && column == other.column;
    }
    bool operator!=(const Cell& other) const { return !(*this == other); }
};
