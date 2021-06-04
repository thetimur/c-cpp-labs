#include "matrix.h"
#include <algorithm>

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    try {
        _data = new int* [r];
    } catch (std::bad_alloc &e) {
        throw e;
    }
    for (std::size_t i = 0; i < r; i++) {
        try {
            _data[i] = new int [c];
        } catch (std::bad_alloc &e) {
            for (int j = (int)i - 1; j >= 0; j--) {
                delete [] _data[j];
            }
            delete [] _data;
            throw e;
        }
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

void Matrix::init(const Matrix &m) noexcept {
    _rows = m._rows;
    _cols = m._cols;
    _data = new int* [_rows];
    for (std::size_t i = 0; i < _rows; i++) {
        _data[i] = new int [_cols];
    }
    copy_data(m._data);
}


void Matrix::copy_data(int** data) noexcept {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = data[i][j];
        }
    }
}

std::size_t Matrix::get_rows() const noexcept { return _rows; }
std::size_t Matrix::get_cols() const noexcept { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) noexcept {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    if (!(i >= 0 && i < _rows && j >= 0 && j < _cols)) {
        throw MatrixException("ACCESS: bad index.");
    }
    return _data[i][j];
}

bool Matrix::operator==(const Matrix& m) const noexcept {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (_data[i][j] != m._data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const noexcept {
    return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if (_cols != m._cols || _rows != m._rows) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    *this = *this + m;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    if (_cols != m._rows) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const noexcept {
    Matrix result(_rows, _cols);
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            result._data[i][j] = m._data[i][j] + _data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& m) const noexcept {
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

void Matrix::print() const noexcept {
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
        throw MatrixException("LOAD: unable to open file.");
    }

    if (fin.eof()) {
        throw MatrixException("LOAD: invalid file format.");
    }
    int rows, cols;
    fin >> rows;

    if (fin.eof()) {
        throw MatrixException("LOAD: invalid file format.");
    }
    fin >> cols;
    Matrix* temp = nullptr;
    try {
        temp = new Matrix(rows, cols);
    } catch (MatrixException &e) {
        throw e;
    }
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            int val;
            if (fin.eof()) {
                throw MatrixException("LOAD: invalid file format.");
            }
            fin >> val;
            temp->set(i, j, val);
        }
    }
    *this = *temp;

    if (fin.eof()) {
        throw MatrixException("LOAD: invalid file format.");
    }
    return *this;
}
