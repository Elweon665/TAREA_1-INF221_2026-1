#include <bits/stdc++.h>
#include <cmath>     
#include <iomanip>  
#include <sstream>
#include "matrix.h"
using namespace std;

Matrix::Matrix(const std::vector<std::vector<double>>& data) : data(data) {
    rows = data.size();
    cols = (rows > 0) ? data[0].size() : 0;
}

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getCols() const {
    return cols;
}

void Matrix::validateDimensions(const Matrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        throw std::runtime_error("Matrices must have the same dimensions.");
    }
}

void Matrix::validateMultiplication(const Matrix& other) const {
    if (getCols() != other.getRows()) {
        throw std::runtime_error("Cannot multiply these matrices.");
    }
}

void Matrix::validateSquarePowerOfTwo() const {
    if (getRows() != getCols()) {
        throw std::runtime_error("Matrix must be square.");
    }
    if (getRows() == 0 || (getRows() & (getRows() - 1)) != 0) {
        throw std::runtime_error("Size of matrix must be a power of two.");
    }
}

Matrix Matrix::operator+(const Matrix& other) const {
    validateDimensions(other);

    std::vector<std::vector<double>> result_data(rows, std::vector<double>(cols));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result_data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return Matrix(result_data);
}

Matrix Matrix::operator-(const Matrix& other) const {
    validateDimensions(other);

    std::vector<std::vector<double>> result_data(rows, std::vector<double>(cols));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result_data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return Matrix(result_data);
}

Matrix Matrix::operator*(const Matrix& other) const {
    validateMultiplication(other);

    std::vector<std::vector<double>> result_data(rows, std::vector<double>(other.cols));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < other.rows; ++k) { // <- 'other.rows' es la clave
                sum += data[i][k] * other.data[k][j];
            }
            result_data[i][j] = sum;
        }
    }

    return Matrix(result_data);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (const auto& row : matrix.data) {
        os << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            os << row[i];
            if (i < row.size() - 1) {
                os << ", ";
            }
        }
        os << "]\n";
    }
    return os;
}

std::string Matrix::toStringWithPrecision(size_t p) const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(p);
    double pow = std::pow(10.0, p);

    for (const auto& row : data) {
        ss << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            double r = std::round(row[i] * pow) / pow;
            std::string formatted = ss.str();
            ss.str(std::string());
            ss << r;
            formatted = ss.str();

            if (formatted == "-0") {
                ss.str(std::string());
                ss << "0";
                formatted = ss.str();
            }

            ss.str(std::string());
            ss << formatted;

            if (i < row.size() - 1) {
                 ss << ", ";
            }
        }
        ss << "]\n";
    }
    return ss.str();
}

std::array<std::array<size_t, 6>, 4> Matrix::params(size_t r, size_t c) {
    return {
        {{{0, r, 0, c, 0, 0}},
         {{0, r, c, 2 * c, 0, c}},
         {{r, 2 * r, 0, c, r, 0}},
         {{r, 2 * r, c, 2 * c, r, c}}}
    };
}

std::array<Matrix, 4> Matrix::toQuarters() const {
    size_t r = getRows() / 2;
    size_t c = getCols() / 2;
    auto p = Matrix::params(r, c);
    std::array<Matrix, 4> quarters = {
        Matrix(std::vector<std::vector<double>>(r, std::vector<double>(c, 0.0))),
        Matrix(std::vector<std::vector<double>>(r, std::vector<double>(c, 0.0))),
        Matrix(std::vector<std::vector<double>>(r, std::vector<double>(c, 0.0))),
        Matrix(std::vector<std::vector<double>>(r, std::vector<double>(c, 0.0)))
    };

    for (size_t k = 0; k < 4; ++k) {
        std::vector<std::vector<double>> q_data(r, std::vector<double>(c));
        for (size_t i = p[k][0]; i < p[k][1]; ++i) {
            for (size_t j = p[k][2]; j < p[k][3]; ++j) {
                q_data[i - p[k][4]][j - p[k][5]] = data[i][j];
            }
        }
        quarters[k] = Matrix(q_data);
    }

    return quarters;
}

Matrix Matrix::fromQuarters(const std::array<Matrix, 4>& q) {
    size_t r = q[0].getRows();
    size_t c = q[0].getCols();
    auto p = Matrix::params(r, c);
    size_t rows = r * 2;
    size_t cols = c * 2;

    std::vector<std::vector<double>> m_data(rows, std::vector<double>(cols, 0.0));

    for (size_t k = 0; k < 4; ++k) {
        for (size_t i = p[k][0]; i < p[k][1]; ++i) {
            for (size_t j = p[k][2]; j < p[k][3]; ++j) {
                m_data[i][j] = q[k].data[i - p[k][4]][j - p[k][5]];
            }
        }
    }

    return Matrix(m_data);
}

/*Matrix Matrix::strassen(const Matrix& other) const {
    validateSquarePowerOfTwo();
    other.validateSquarePowerOfTwo();
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        throw std::runtime_error("Matrices must be square and of equal size for Strassen multiplication.");
    }

    if (getRows() == 1) {
        double valor_multiplicado = data * other.data;
        
        // 2. Retornamos una nueva Matriz construyéndola con llaves (mucho más legible)
        return Matrix({{valor_multiplicado}});
    }

    auto qa = toQuarters();
    auto qb = other.toQuarters();

    Matrix p1 = (qa[1] - qa[3]).strassen(qb[2] + qb[3]);
    Matrix p2 = (qa[0] + qa[3]).strassen(qb[0] + qb[3]);
    Matrix p3 = (qa[0] - qa[2]).strassen(qb[0] + qb[1]);
    Matrix p4 = (qa[0] + qa[1]).strassen(qb[3]);
    Matrix p5 = qa[0].strassen(qb[1] - qb[3]);
    Matrix p6 = qa[3].strassen(qb[2] - qb[0]);
    Matrix p7 = (qa[2] + qa[3]).strassen(qb[0]);

    std::array<Matrix, 4> q = {
        Matrix(std::vector<std::vector<double>>(qa[0].getRows(), std::vector<double>(qa[0].getCols(), 0.0))),
        Matrix(std::vector<std::vector<double>>(qa[0].getRows(), std::vector<double>(qa[0].getCols(), 0.0))),
        Matrix(std::vector<std::vector<double>>(qa[0].getRows(), std::vector<double>(qa[0].getCols(), 0.0))),
        Matrix(std::vector<std::vector<double>>(qa[0].getRows(), std::vector<double>(qa[0].getCols(), 0.0)))
    };

    q[0] = p1 + p2 - p4 + p6;
    q[1] = p4 + p5;
    q[2] = p6 + p7;
    q[3] = p2 - p3 + p5 - p7;

    return Matrix::fromQuarters(q);
}*/

Matrix Matrix::strassen(const Matrix& other) const {
    validateSquarePowerOfTwo();
    other.validateSquarePowerOfTwo();
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        throw std::runtime_error("Matrices must be square and of equal size for Strassen multiplication.");
    }

    // 1. CASO BASE OPTIMIZADO A PRUEBA DE ERRORES DE COMPILACIÓN
    if (getRows() == 1) {
        // Creamos un vector 2D de 1x1 inicializado en 0 explícitamente
        std::vector<std::vector<double>> res(1, std::vector<double>(1, 0.0));
        // Multiplicamos los doubles extrayéndolos con
        res = data * other.data;
        // Retornamos la matriz
        return Matrix(res);
    }

    auto qa = toQuarters();
    auto qb = other.toQuarters();

    Matrix p1 = (qa - qa).strassen(qb + qb);
    Matrix p2 = (qa + qa).strassen(qb + qb);
    Matrix p3 = (qa - qa).strassen(qb + qb);
    Matrix p4 = (qa + qa).strassen(qb);
    Matrix p5 = qa.strassen(qb - qb);
    Matrix p6 = qa.strassen(qb - qb);
    Matrix p7 = (qa + qa).strassen(qb);

    std::array<Matrix, 4> q = {
        Matrix(std::vector<std::vector<double>>(qa.getRows(), std::vector<double>(qa.getCols(), 0.0))),
        Matrix(std::vector<std::vector<double>>(qa.getRows(), std::vector<double>(qa.getCols(), 0.0))),
        Matrix(std::vector<std::vector<double>>(qa.getRows(), std::vector<double>(qa.getCols(), 0.0))),
        Matrix(std::vector<std::vector<double>>(qa.getRows(), std::vector<double>(qa.getCols(), 0.0)))
    };

    // 2. OPTIMIZACIÓN DE MEMORIA: Suma directa elemento por elemento
    // (Esto evita que la matriz de 1024x1024 se quede colgada)
    size_t sub_n = qa.getRows();
    for (size_t i = 0; i < sub_n; ++i) {
        for (size_t j = 0; j < sub_n; ++j) {
            q.data[i][j] = p1.data[i][j] + p2.data[i][j] - p4.data[i][j] + p6.data[i][j];
            q.data[i][j] = p4.data[i][j] + p5.data[i][j];
            q.data[i][j] = p6.data[i][j] + p7.data[i][j];
            q.data[i][j] = p2.data[i][j] - p3.data[i][j] + p5.data[i][j] - p7.data[i][j];
        }
    }

    return Matrix::fromQuarters(q);
}