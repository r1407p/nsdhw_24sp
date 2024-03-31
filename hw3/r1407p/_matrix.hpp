#pragma once

#include <vector>
using namespace std;

class Matrix{
private:
    size_t row, col;
    double *matrix;
public:
    Matrix();
    Matrix(size_t row, size_t col);
    Matrix(size_t row, size_t col, double val);
    Matrix(size_t row, size_t col,const vector<double> &v);
    Matrix(const Matrix &m);
    size_t get_index(size_t i, size_t j);
    size_t get_row();
    size_t get_col();
    ~Matrix();

    double operator()(size_t i, size_t j);
    void operator()(size_t i, size_t j, double val);
};