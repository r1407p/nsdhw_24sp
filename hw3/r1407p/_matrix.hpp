#pragma once

#include <vector>
using namespace std;

class Matrix{
private:
    size_t m_nrow, m_ncol;
    double *m_buffer;
    bool m_transpose;
public:
    Matrix();
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, double val);
    Matrix(size_t nrow, size_t ncol,const vector<double> &v);
    Matrix(const Matrix &m);
    size_t index(size_t i, size_t j) const;
    size_t nrow() const;
    size_t ncol() const;
    const double* get_buffer() const;

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
    bool is_transposed() const;
    Matrix & transpose();
};