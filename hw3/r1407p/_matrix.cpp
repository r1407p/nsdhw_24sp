#include "_matrix.hpp"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
Matrix::Matrix(){
    this->row = 0;
    this->col = 0;
    this->matrix = nullptr;
}

Matrix::Matrix(size_t row, size_t col){
    this->row = row;
    this->col = col;
    this->matrix = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        this->matrix[i] = 0;
    }
}

Matrix::Matrix(size_t row, size_t col, double val){
    this->row = row;
    this->col = col;
    this->matrix = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        this->matrix[i] = val;
    }
}

Matrix::Matrix(size_t row, size_t col,const std::vector<double> &v){
    this->row = row;
    this->col = col;
    this->matrix = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        if (i < v.size()){
            this->matrix[i] = v[i];
        }else{
            this->matrix[i] = 0;
        }
    }
}
Matrix::Matrix(const Matrix &m){
    this->row = m.row;
    this->col = m.col;
    this->matrix = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        this->matrix[i] = m.matrix[i];
    }
} 
size_t Matrix::get_index(size_t i, size_t j){
    return i * this->col + j;
}
size_t Matrix::get_row(){
    return this->row;
}
size_t Matrix::get_col(){
    return this->col;
}
Matrix::~Matrix(){
    delete[] this->matrix;
}

double Matrix::operator()(size_t i, size_t j){
    return this->matrix[get_index(i, j)];
}
void Matrix::operator()(size_t i, size_t j, double val){
    this->matrix[get_index(i, j)] = val;
}

PYBIND11_MODULE(_matrix, m) {
    m.doc() = "pybind11 matrix plugin"; // optional module docstring
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, double>())
        .def(py::init<size_t, size_t, const std::vector<double> &>())
        .def(py::init<const Matrix &>());
        
}