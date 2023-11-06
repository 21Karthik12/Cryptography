#ifndef AES_WORDLIST
#define AES_WORDLIST

#include "word.hpp"

class WordList {
private:
    std::vector<Word> words;
public:
    WordList() : words(std::vector<Word>(4)) {}

    WordList(std::vector<Word> words) : words(words) {}

    void operator= (std::vector<Word> list) {
        for (int i = 0; i < 4; i++) {
            words[i] = list[i];
        }
    }

    void operator= (WordList list) {
        for (int i = 0; i < 4; i++) {
            words[i] = list[i];
        }
    }

    Word& operator[] (int i) {
        return words[i];
    }

    friend std::ostream& operator<< (std::ostream& strm, WordList list) {
        strm << "╔══╤══╤══╤══╗\n";
        for (int col = 0; col < 4; col++) {
            strm << "║";
            for (int row = 0; row < 4; row++) {
                strm << list[row][col].get_value();
                if (row == 3) {
                    strm << "║";
                }
                else {
                    strm << "│";
                }
            }
            strm << "\n";
            if (col != 3) {
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