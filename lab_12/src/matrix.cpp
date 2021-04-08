#include "matrix.h"
#include <algorithm>

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int* [r];
    for (std::size_t i = 0; i < r; i++) {
        _data[i] = new int [c];
        std::fill(_data[i], _data[i] + c, 0);
    }
}

Matrix::Matrix(const Matrix& m) {
    init(m);
}

Matrix& Matrix::operator=(const Matrix &m) {
    for (std::size_t i = 0; i < _rows; i++) {
        delete [] _data[i];
    }
    delete [] _data;
    init(m);
    return *this;
}

Matrix::~Matrix() {
    for (std::size_t i = 0; i < _rows; i++) {
        delete [] _data[i];
    }
    delete [] _data;
}

void Matrix::init(const Matrix &m) {
    _rows = m._rows;
    _cols = m._cols;
    _data = new int* [_rows];
    for (std::size_t i = 0; i < _rows; i++) {
        _data[i] = new int [_cols];
    }
    copy_data(m._data);
}


void Matrix::copy_data(int** data) {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = data[i][j];
        }
    }
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    if (!(i >= 0 && i < _rows && j >= 0 && j < _cols)) {
        throw BadIndexMatrixException();
    }
    return _data[i][j];
}

bool Matrix::operator==(const Matrix& m) const {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (_data[i][j] != m._data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if (_cols != m._cols || _rows != m._cols) {
        throw AddMatrixException();
    }
    *this = *this + m;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    if (_cols != m._rows) {
        throw MultiplyMatrixException();
    }
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix result(_rows, _cols);
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            result._data[i][j] = m._data[i][j] + _data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix result(_rows, m._cols);
    for (std::size_t i = 0; i < result.get_rows(); i++) {
        for (std::size_t j = 0; j < result.get_cols(); j++) {
            int sum = 0;
            for (std::size_t k = 0; k < _cols; k++) {
                sum += _data[i][k] * m.get(k, j);
            }
            result._data[i][j] = sum;
        }
    }
    return result;
}

void Matrix::print() const {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (j) {
                std::cout << " ";
            }
            std::cout << _data[i][j];
        }
        std::cout << std::endl;
    }
}

Matrix& Matrix::load(const std::string filename) {
    std::ifstream fin;
    fin.open(filename, std::ios::binary);
    if (fin.fail()) {
        throw LoadMatrixException("unable to open file.");
    }

    if (fin.eof()) {
        throw LoadMatrixException("invalid file format.");
    }
    int rows, cols;
    fin >> rows;

    if (fin.eof()) {
        throw LoadMatrixException("invalid file format.");
    }
    fin >> cols;

    Matrix temp(rows, cols);
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            int val;
            if (fin.eof()) {
                throw LoadMatrixException("invalid file format.");
            }
            fin >> val;
            temp._data[i][j] = val;
        }
    }
    *this = temp;

    return *this;
}
