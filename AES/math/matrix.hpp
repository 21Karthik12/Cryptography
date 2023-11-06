#ifndef AES_MATRIX
#define AES_MATRIX

#include <vector>
#include "polynomial.hpp"

class Matrix {
private:
    std::vector<std::vector<Polynomial>> values;

public:
    Matrix() {
        values = std::vector<std::vector<Polynomial>>(4, std::vector<Polynomial>(4));
    }

    Matrix(std::vector<std::vector<Polynomial>> values) : values(values) {}

    void operator= (Matrix matrix) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                values[row][col] = matrix.values[row][col];
            }
        }
    }

    void operator= (std::vector<std::vector<Polynomial>> list) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                values[row][col] = list[row][col];
            }
        }
    }

    Matrix operator+ (Matrix matrix) {
        Matrix result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result[row][col] = (values[row][col] + matrix.values[row][col]);
            }
        }
        return result;
    }

    void operator+= (Matrix matrix) {
        operator= (operator+ (matrix));
    }

    Matrix operator- (Matrix matrix) {
        return operator+ (matrix);
    }

    void operator-= (Matrix matrix) {
        operator= (operator- (matrix));
    }

    Matrix operator* (Matrix matrix) {
        Matrix result;
        for (int row1 = 0; row1 < 4; row1++) {
            for (int col2 = 0; col2 < 4; col2++) {
                for (int col1 = 0; col1 < 4; col1++) {
                    result[row1][col2] += (values[row1][col1] * matrix.values[col1][col2]);
                }
            }
        }
        return result;
    }

    void operator*= (Matrix matrix) {
        operator* (operator* (matrix));
    }

    std::vector<Polynomial>& operator[] (int i) {
        return values[i];
    }

    friend std::ostream& operator<<(std::ostream& strm, Matrix matrix) {
        strm << "╔══╤══╤══╤══╗\n";
        for (int row = 0; row < 4; row++) {
            strm << "║";
            for (int col = 0; col < 4; col++) {
                strm << matrix[row][col].get_value();
                if (col == 3) {
                    strm << "║";
                }
                else {
                    strm << "│";
                }
            }
            strm << "\n";
            if (row != 3) {
                strm << "╟──┼──┼──┼──╢\n";
            }
            else {
                strm << "╚══╧══╧══╧══╝\n";
            }
        }
        return strm;
    }
};

#endif