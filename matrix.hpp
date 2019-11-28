#ifndef MATRIX_H_
#define MATRIX_H_


#include <cstdio>
//! From Politecnico di Milano course of Algorthms and Parallel Computing by Danilo Ardagna

class Matrix
{
protected:
    size_t n_rows;
    size_t n_cols;

    bool indexes_in_range(size_t i, size_t j) const;

public:
    Matrix (size_t rows, size_t cols);

    size_t get_n_cols() const;
    size_t get_n_rows() const;

    virtual ~Matrix () = default;
};

#endif /* MATRIX_H_ */
