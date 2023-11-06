#ifndef AES_WORD
#define AES_WORD

#include "../math/polynomial.hpp"
#include <vector>

class Word {
private:
    std::vector<Polynomial> list;

public:
    Word() {
        list = std::vector<Polynomial>(4);
    }

    Word(std::vector<Polynomial> list) : list(list) {}

    void operator= (Word word) {
        for (int i = 0; i < 4; i++) {
            list[i] = word[i];
        }
    }

    void operator= (std::vector<Polynomial> word) {
        for (int i = 0; i < 4; i++) {
            list[i] = word[i];
        }
    }

    Word operator+ (Word word) {
        Word result;
        for (int i = 0; i < 4; i++) {
            result[i] = (list[i] + word[i]);
        }
        return result;
    }

    void operator+= (Word word) {
        operator= (operator+ (word));
    }

    Polynomial& operator[] (int i) {
        return list[i];
    }

    friend std::ostream& operator<<(std::ostream& strm, Word word) {
        strm << "╔══╤══╤══╤══╗\n";
        strm << "║";
        for (int col = 0; col < 4; col++) {
            strm << word[col].get_value();
            if (col == 3) {
                strm << "║";
            }
            else {
                strm << "│";
            }
        }
        strm << "\n";
        strm << "╚══╧══╧══╧══╝\n";
        return strm;
    }
};

#endif