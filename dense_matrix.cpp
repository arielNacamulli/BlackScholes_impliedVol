#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "dense_matrix.hpp"

DenseMatrix::DenseMatrix (std::size_t rows, std::size_t columns, const double & value) :
   Matrix(rows, columns),
   m_data (n_rows * n_cols, value)
{
}

DenseMatrix::DenseMatrix(std::size_t rows, std::size_t columns, std::vector<double> values) :
   Matrix(rows, columns),
   m_data(values)
{}

std::size_t
DenseMatrix::sub2ind (std::size_t i, std::size_t j) const
{
   return i * n_cols + j;
}

   void
DenseMatrix::read (std::istream & in)
{
   std::string line;
   std::getline (in, line);

   std::istringstream first_line (line);
   first_line >> n_rows >> n_cols;
   m_data.resize (n_rows * n_cols);

   for (std::size_t i = 0; i < n_rows; ++i)
   {
      std::getline (in, line);
      std::istringstream current_line (line);

      for (std::size_t j = 0; j < n_cols; ++j)
      {
         /* alternative syntax: current_line >> operator () (i, j);
          * or: current_line >> m_data[sub2ind (i, j)];
          */
         current_line >> (*this)(i, j);
      }
   }
}

   void
DenseMatrix::swap (DenseMatrix & rhs)
{
   using std::swap;
   swap (n_rows, rhs.n_rows);
   swap (n_cols, rhs.n_cols);
   swap (m_data, rhs.m_data);
}

std::size_t
DenseMatrix::rows (void) const
{
   return n_rows;
}

std::size_t
DenseMatrix::columns (void) const
{
   return n_cols;
}

DenseMatrix
DenseMatrix::transposed (void) const
{
   DenseMatrix At (n_cols, n_rows);

   for (std::size_t i = 0; i < n_cols; ++i)
      for (std::size_t j = 0; j < n_rows; ++j)
         At(i, j) = operator () (j, i);

   return At;
}

   double *
DenseMatrix::data (void)
{
   return m_data.data ();
}

const double *
DenseMatrix::data () const
{
   return m_data.data ();
}

   DenseMatrix
operator * (DenseMatrix const & A, DenseMatrix const & B)
{
   DenseMatrix C (A.rows (), B.columns ());

   for (std::size_t i = 0; i < A.rows (); ++i)
      for (std::size_t j = 0; j < B.columns (); ++j)
         for (std::size_t k = 0; k < A.columns (); ++k)
            C(i, j) += A(i, k) * B(k, j);

   return C;
}

   void
swap (DenseMatrix & A, DenseMatrix & B)
{
   A.swap (B);
}

double & DenseMatrix::operator()(std::size_t i, std::size_t j)
{
   return m_data.at(sub2ind(i, j));
}

double DenseMatrix::operator()(std::size_t i, std::size_t j) const
{
   return m_data.at(sub2ind(i, j));
}

void DenseMatrix::print() const {
    for(size_t i = 0;i<columns();i++) {
        for(size_t j = 0;j<rows();j++)
            std::cout << std::setw(14) << (*this)(i,j);
        std::cout << std::endl;
    }
}
