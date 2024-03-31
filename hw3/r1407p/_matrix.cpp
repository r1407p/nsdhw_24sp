#include "_matrix.hpp"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
Matrix::Matrix(){
    this->m_nrow = 0;
    this->m_ncol = 0;
    this->m_buffer = nullptr;
}

Matrix::Matrix(size_t nrow, size_t ncol){
    this->m_nrow = nrow;
    this->m_ncol = ncol;
    this->m_buffer = new double[nrow * ncol];
    for(size_t i = 0; i < nrow * ncol; i++){
        this->m_buffer[i] = 0;
    }
}

Matrix::Matrix(size_t row, size_t col, double val){
    this->m_nrow = row;
    this->m_ncol = col;
    this->m_buffer = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        this->m_buffer[i] = val;
    }
}

Matrix::Matrix(size_t row, size_t col,const std::vector<double> &v){
    this->m_nrow = row;
    this->m_ncol = col;
    this->m_buffer = new double[row * col];
    if(v.size() != row * col){
        throw std::invalid_argument("size of vector does not match matrix size");
    }
    for(size_t i = 0; i < row * col; i++){
        this->m_buffer[i] = v[i];
    }
}
Matrix::Matrix(const Matrix &m){
    this->m_nrow = m.m_nrow;
    this->m_ncol = m.m_ncol;
    this->m_buffer = new double[m.m_nrow * m.m_ncol];
    for(size_t i = 0; i < m.m_nrow * m.m_ncol; i++){
        this->m_buffer[i] = m.m_buffer[i];
    }
} 
size_t Matrix::index(size_t i, size_t j) const{
    return i * this->m_ncol + j;
}
size_t Matrix::nrow(){
    return this->m_nrow;
}
size_t Matrix::ncol(){
    return this->m_ncol;
}
Matrix::~Matrix(){
    delete[] this->m_buffer;
}

double Matrix::operator() (size_t row, size_t col) const{
    if (row < 0 || row >= m_nrow || col < 0 || col > m_ncol){
        throw std::out_of_range("index out of range");
    }
    return m_buffer[index(row, col)];
}
double &Matrix::operator() (size_t row, size_t col){
    if (row < 0 || row >= m_nrow || col < 0 || col > m_ncol){
        throw std::out_of_range("index out of range");
    }
    return m_buffer[index(row, col)];
}

bool Matrix::is_transposed() const{
    return m_transpose;
}
Matrix & Matrix::transpose(){
    m_transpose = !m_transpose;
    std::swap(m_nrow, m_ncol);
    return *this;
}
PYBIND11_MODULE(_matrix, m) {
    m.doc() = "pybind11 matrix plugin"; // optional module docstring
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, double>())
        .def(py::init<size_t, size_t, const std::vector<double> &>())
        .def(py::init<const Matrix &>())
        .def("__getitem__", [](const Matrix &m, std::vector<std::size_t> idx){ 
            return m(idx[0], idx[1]); 
        })
        .def("__setitem__", [](Matrix &m, std::vector<std::size_t> idx, double val){
             m(idx[0], idx[1]) = val; 
        });
      
        
}