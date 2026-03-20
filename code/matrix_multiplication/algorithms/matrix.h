#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <array>
#include <string>
#include <iostream>

std::vector<std::vector<int>> naive(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B);

class Matrix {
public:
    std::vector<std::vector<double>> data;
    size_t rows;
    size_t cols;

    Matrix(const std::vector<std::vector<double>>& data);

    size_t getRows() const;
    size_t getCols() const;

    void validateDimensions(const Matrix& other) const;
    void validateMultiplication(const Matrix& other) const;
    void validateSquarePowerOfTwo() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    std::string toStringWithPrecision(size_t p) const;
    static std::array<std::array<size_t, 6>, 4> params(size_t r, size_t c);
    std::array<Matrix, 4> toQuarters() const;
    static Matrix fromQuarters(const std::array<Matrix, 4>& q);

    Matrix strassen(const Matrix& other) const;
};

#endif