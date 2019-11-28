#include "matrix.hpp"

Matrix::Matrix (size_t rows, size_t cols)
  : n_rows (rows), n_cols (cols) {}

size_t Matrix::get_n_cols() const {
    return n_cols;
}

size_t Matrix::get_n_rows() const {
    return n_rows;
}

bool Matrix::indexes_in_range(size_t i, size_t j) const {
    return i < n_rows && j < n_cols;
}

