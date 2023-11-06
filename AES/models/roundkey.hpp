#ifndef AES_ROUND_KEY
#define AES_ROUND_KEY

#include "wordlist.hpp"
#include "../math/matrix.hpp"
#include <vector>

class RoundKey : public Matrix {
public:
    RoundKey() : Matrix() {}

    RoundKey(std::vector<std::vector<Polynomial>> keys) : Matrix(keys) {}

    RoundKey(WordList words) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                operator[](row)[col] = words[col][row];
            }
        }
    }

    WordList to_words() {
        WordList result;
        for (int col = 0; col < 4; col++) {
            Word word;
            for (int row = 0; row < 4; row++) {
                word[row] = operator[](row)[col];
            }
            result[col] = word;
        }
        return result;
    }
};

#endif