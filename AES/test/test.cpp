#include <bits/stdc++.h>
#include "../operations/sbox.hpp"
#include "../operations/shiftrows.hpp"
#include "../operations/mixcolumns.hpp"
#include "../operations/addroundkey.hpp"

int main() {
    SBox box;
    box.transform();

    DataBlock input({
        {0x01, 0x89, 0xFE, 0x76},
        {0x23, 0xAB, 0xDC, 0x54},
        {0x45, 0xCD, 0xBA, 0x32},
        {0x67, 0xEF, 0x98, 0x10}
    });

    DataBlock block = input;
    std::cout << block;

    RoundKey initial_key = RoundKey({
        {0x0F, 0x47, 0x0C, 0xAF},
        {0x15, 0xD9, 0xB7, 0x7F},
        {0x71, 0xE8, 0xAD, 0x67},
        {0xC9, 0x59, 0xD6, 0x98}
    });

    RoundKeyList key_list(initial_key);

    block = key_list.add_round_key(block, 0);
    std::cout << block;

    block = box.substitute(block);
    std::cout << block;

    block = ShiftRows::shift(block);
    std::cout << block;

    block = MixColumns::mix(block);
    std::cout << block;

    return 0;
}