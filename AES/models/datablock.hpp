#ifndef AES_DATABLOCK
#define AES_DATABLOCK

#include <vector>
#include "../math/matrix.hpp"

class DataBlock : public Matrix {
public:
    DataBlock() : Matrix() {}

    DataBlock(const std::vector<char>& chars) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                operator[](row)[col] = chars[(4 * col) + row];
            }
        }
    }

    DataBlock(std::vector<std::vector<Polynomial>> values) : Matrix(values) {}

    DataBlock(Matrix matrix) : Matrix(matrix) {}
};

#endif