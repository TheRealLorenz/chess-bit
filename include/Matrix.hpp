#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>

template <typename T, size_t R, size_t C = R>
class Matrix {
public:
    const T& get(size_t row, size_t column) const {
        checkAccess(row, column);
        return buffer[row * R + column];
    }
    T& get(size_t row, size_t column) {
        return const_cast<T>(static_cast<const Matrix>(*this).get(row, column));
    }
    void swap(size_t row1, size_t column1, size_t row2, size_t column2) {
        checkAccess(row1, column1);
        checkAccess(row2, column2);
        std::swap(buffer[row1 * R + column1], buffer[row2 * R + column2]);
    }

    void set(size_t row, size_t column, T item) {
        checkAccess(row, column);
        buffer[row * R + column] = item;
    }

    auto begin() const { return buffer.begin(); }
    auto end() const { return buffer.end(); }

private:
    inline void checkAccess(size_t row, size_t column) const {
        if (row >= R) {
            throw std::out_of_range("Invalid row number '" +
                                    std::to_string(row) + "'");
        }
        if (column >= C) {
            throw std::out_of_range("Invalid column number '" +
                                    std::to_string(column) + "'");
        }
    }

    std::array<T, R * C> buffer;
};