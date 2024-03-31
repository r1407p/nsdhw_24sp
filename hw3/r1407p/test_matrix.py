import pytest
import _matrix
import timeit

def make_matrices( size):

        mat1 = _matrix.Matrix(size,size)
        mat2 = _matrix.Matrix(size,size)
        mat3 = _matrix.Matrix(size,size)

make_matrices(100)

