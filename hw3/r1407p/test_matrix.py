import _matrix 
import pytest
import timeit
import random

def test_constructer():
    
    col = random.randint(1, 1000)
    row = random.randint(1, 1000)
    matrix = _matrix.Matrix(row, col)
    
    assert matrix.nrow == row
    assert matrix.ncol == col
    for i in range(row):
        for j in range(col):
            assert matrix[i, j] == 0 
    
def test_multiply_correctness():
    size1 = random.randint(1, 1000)
    size2 = random.randint(1, 1000)
    size3 = random.randint(1, 1000)
    ori_matrix1 = _matrix.Matrix(size1, size2)
    ori_matrix2 = _matrix.Matrix(size2, size3)
    for i in range(size1):
        for j in range(size2):
            ori_matrix1[i, j] = random.randint(1, 1000)
    for i in range(size2):
        for j in range(size3):
            ori_matrix2[i, j] = random.randint(1, 1000)
    ret_matrix1 = _matrix.multiply_naive(ori_matrix1, ori_matrix2)
    ret_matrix2 = _matrix.multiply_tile(ori_matrix1, ori_matrix2,64)
    ret_matrix3 = _matrix.multiply_mkl(ori_matrix1, ori_matrix2)
    
    for i in range(size1):
        for j in range(size3):
            assert ret_matrix1[i, j] == ret_matrix2[i, j] == ret_matrix3[i, j]
    
def test_performance():
    setup = '''
import _matrix

size = 1000

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
tile_size = 64
'''
    
    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)
    tile = timeit.Timer('_matrix.multiply_tile(mat1, mat2, tile_size)', setup=setup)
    
    repeat = 5
    with open('performance.txt', 'w') as fobj:

        w = Writer([sys.stdout, fobj])

        w.write(f'Start multiply_naive (repeat={repeat}), take min = ')
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_mkl (repeat={repeat}), take min = ')
        mklsec = minsec = min(mkl.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile (repeat={repeat}), take min = ')
        tilesec = minsec = min(tile.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')
        
        w.write('MKL speed-up over naive: %g x\n' % (naivesec/mklsec))
        w.write('Tile speed-up over naive: %g x\n' % (naivesec/tilesec))