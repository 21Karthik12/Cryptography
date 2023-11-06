#ifndef AES_ADD_ROUND_KEY
#define AES_ADD_ROUND_KEY

#include "../models/roundkey.hpp"
#include "sbox.hpp"
#include "../models/datablock.hpp"

class RoundKeyList {
private:
    Word rot_word(Word w) {
        Word result;
        for (int i = 0; i < 4; i++) {
            result[i] = w[(i + 1) % 4];
        }
        return result;
    }

    Word sub_word(Word w) {
        Word result;
        for (int i = 0; i < 4; i++) {
            result[i] = box[w[i]];
        }
        return result;
    }

    Word add_round_constant(Word w, int round) {
        return (w + round_constants[round]);
    }

    Word auxiliary(Word w, int round) {
        return add_round_constant(sub_word(rot_word(w)), round);
    }

    WordList next_key(WordList list, int round) {
        WordList result;
        result[0] = (list[0] + auxiliary(list[3], round));
        for (int i = 1; i < 4; i++) {
            result[i] = (result[i - 1] + list[i]);
        }
        return result;
    }

    std::vector<RoundKey> keys;

    SBox box;

    std::vector<Word> round_constants;

public:

    RoundKeyList(RoundKey initial_key) {
        box.transform();

        round_constants = std::vector<Word>(11);
        std::vector<Polynomial> rcon = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10,
                                        0x20, 0x40, 0x80, 0x1B, 0x36};
        for (int i = 0; i < 11; i++) {
            round_constants[i] = {rcon[i], 0, 0, 0};
        }

        keys = std::vector<RoundKey>(11);
        keys[0] = initial_key;
        for (int round = 1; round < 11; round++) {
            keys[round] = next_key(keys[round - 1].to_words(), round);
        }
    }

    RoundKey& operator[] (int i) {
        return keys[i];
    }

    DataBlock add_round_key(DataBlock block, int round) {
        return (block + keys[round]);
    }
};

#endif