#ifndef AES_BITLIST
#define AES_BITLIST

#include "bit.hpp"
#include <vector>

class BitList {
private:
    std::vector<Bit> bits;

public:
    BitList() {}

    BitList(uint bitstring) {
        do {
            bits.emplace_back(bitstring & 1);
            bitstring >>= 1;
        } while (bitstring > 0);
    }

    BitList(const std::string& bitstring) {
        for (int i = bitstring.size() - 1; i >= 0; i--) {
            bits.emplace_back(bitstring[i] - '0');
        }
    }

    Bit& operator[] (int i) {
        if (i < bits.size()) {
            return bits[i];
        }
        for (int j = bits.size(); j <= i; j++) {
            bits.push_back(0);
        }
        return bits[i];
    }

    void operator= (uint bitstring) {
        bits.clear();
        do {
            bits.emplace_back(bitstring & 1);
            bitstring >>= 1;
        } while (bitstring > 0);
    }

    void operator= (const std::string& bitstring) {
        bits.clear();
        for (int i = bitstring.size() - 1; i >= 0; i--) {
            bits.emplace_back(bitstring[i] - '0');
        }
    }

    void operator= (const BitList& list) {
        bits.clear();
        size_t size = list.bits.size();
        for (int i = 0; i < size; i++) {
            bits.emplace_back(list.bits[i]);
        }
    }

    bool operator== (const BitList& list) {
        if (bits.size() != list.bits.size()) {
            return false;
        }
        for (int i = 0; i < bits.size(); i++) {
            if (bits[i] != list.bits[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!= (const BitList& list) {
        return !operator== (list);
    }

    void add(Bit bit) {
        bits.push_back(bit);
    }

    void add_front(Bit bit) {
        bits.insert(bits.begin(), bit);
    }

    size_t size() {
        return bits.size();
    }

    void pop() {
        bits.pop_back();
    }

    void left_shift() {
        add_front(0);
    }
};

#endif