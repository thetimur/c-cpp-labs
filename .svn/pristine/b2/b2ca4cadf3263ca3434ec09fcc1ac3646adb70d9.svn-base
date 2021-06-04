#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>
#include <fstream>
#include <iostream>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix &m);
    ~Matrix();

    std::size_t get_rows() const noexcept;
    std::size_t get_cols() const noexcept;
    void set(std::size_t i, std::size_t j, int val) noexcept;
    int get(std::size_t i, std::size_t j) const;

    Matrix operator+(const Matrix& m) const noexcept;
    Matrix operator*(const Matrix& m) const noexcept;

    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& load(const std::string filename);
    void print() const noexcept;


    bool operator==(const Matrix& m) const noexcept;
    bool operator!=(const Matrix& m) const noexcept;
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
    void copy_data(int** data) noexcept;
    void init(const Matrix &m) noexcept;
};

class MatrixException : public std::logic_error {
public:
    MatrixException(std::string _message) : logic_error(_message) {}
};

#endif