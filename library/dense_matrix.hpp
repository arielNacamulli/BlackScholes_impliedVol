#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include <istream>
#include <vector>

#include "matrix.hpp"

//! From Politecnico di Milano course of Algorthms and Parallel Computing by Danilo Ardagna

class DenseMatrix : public Matrix
{
private:
   std::vector<double> m_data;

   std::size_t sub2ind (std::size_t i, std::size_t j) const;

public:
   DenseMatrix (std::size_t rows, std::size_t columns,
         const double & value = 0.0);

   DenseMatrix (std::size_t rows, std::size_t columns,
         std::vector<double> values);

   void read (std::istream &);

   void swap (DenseMatrix &);

   double & operator () (std::size_t i, std::size_t j);

   double operator () (std::size_t i, std::size_t j) const;

   std::size_t rows () const;
   std::size_t columns () const;
   DenseMatrix transposed () const;
   double * data ();
   const double * data () const;

   void print() const;
};

DenseMatrix operator * (DenseMatrix const &, DenseMatrix const &);

void swap (DenseMatrix &, DenseMatrix &);

#endif // DENSE_MATRIX_HH
