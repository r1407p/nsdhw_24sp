#include "matrix.hpp"
using namespace std;

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

Matrix::Matrix(size_t row, size_t col,const vector<double> &v){
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
int Matrix::get_index(size_t i, size_t j){
    return i * this->col + j;
}
Matrix::~Matrix(){
    delete[] this->matrix;
}
