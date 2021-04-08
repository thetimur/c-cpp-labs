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

    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;

    Matrix operator+(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& load(const std::string filename);
    void print() const;


    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
    void copy_data(int** data);
    void init(const Matrix &m);
};

class MatrixException {
public:
    MatrixException(std::string _space, std::string _message) : space(_space), message(_message) {}
    void print() {
        std::cout << space << ": " << message << std::endl;
    }
private:
    std::string space, message;
};

class LoadMatrixException : public MatrixException {
public:
    LoadMatrixException(std::string message) : MatrixException("LOAD", message) {}
};

class AddMatrixException : public MatrixException {
public:
    AddMatrixException() : MatrixException("ADD", "dimensions do not match.") {}
};

class MultiplyMatrixException : public MatrixException {
public:
    MultiplyMatrixException() : MatrixException("MUL", "#arg1.columns != #arg2.rows.") {}
};

class BadIndexMatrixException : public MatrixException {
public:
    BadIndexMatrixException() : MatrixException("ACCESS", "bad index.") {}
};


#endif