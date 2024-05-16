#pragma once

#include "Cell.hpp"

struct Move {
    enum class Type {
        Regualar,
        DoublePawn,
        Castle,
        EnPassantCapture,
        ShortCastling,
        LongCastling
    };

    explicit Move(Cell cell, Type type = Move::Type::Regualar)
        : type(type), cell(cell) {}

    const Type type;
    const Cell cell;

    Move operator=(Move other) { return Move{other.cell, other.type}; }
};
