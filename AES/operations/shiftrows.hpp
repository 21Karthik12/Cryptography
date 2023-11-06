#ifndef AES_SHIFT_ROWS
#define AES_SHIFT_ROWS

#include "../models/datablock.hpp"

class ShiftRows {
public:
    static DataBlock shift(DataBlock block) {
        DataBlock result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result[row][col] = block[row][(col + row) % 4];
            }
        }
        return result;
    }
    
    static DataBlock inverse_shift(DataBlock block) {
        DataBlock result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result[row][col] = block[row][(4 + col - row) % 4];
            }
        }
        return result;
    }
};

#endif