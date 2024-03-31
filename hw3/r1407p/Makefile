sources = _matrix.cpp
tests = test_matrix.py
executable = _matrix$(shell python3-config --extension-suffix)
CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` -I/usr/include/mkl
MKL_LIB_DIR=/usr/lib/x86_64-linux-gnu
MKL_LIB_SO=libmkl_def.so libmkl_avx2.so libmkl_core.so libmkl_intel_lp64.so libmkl_sequential.so
MKL_LIBS=$(patsubst %, $(MKL_LIB_DIR)/%, $(MKL_LIB_SO)) -lpthread -lm -ldl -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

all: $(sources)
	$(CXX) $(CXXFLAGS) $(MKL_LIBS) $ $(shell python3 -m pybind11 --includes) $(sources) -o $(executable)

test: all
	python3 -m pytest

clean:
	rm -rf $(executable) __pycache__ .pytest* *.so