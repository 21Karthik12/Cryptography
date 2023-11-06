#include <bits/stdc++.h>

#include "../operations/sbox.hpp"
#include "../operations/shiftrows.hpp"
#include "../operations/mixcolumns.hpp"
#include "../operations/addroundkey.hpp"

using namespace std;

DataBlock encrypt(DataBlock input) {
    cout << "Encrypting...\n";

    SBox box;
    box.transform();
    RoundKey initial_key = RoundKey({
        {0x0F, 0x47, 0x0C, 0xAF},
        {0x15, 0xD9, 0xB7, 0x7F},
        {0x71, 0xE8, 0xAD, 0x67},
        {0xC9, 0x59, 0xD6, 0x98}
    });
    RoundKeyList key_list(initial_key);

    DataBlock block = input;

    cout << "Round-0:\n";
    
    cout << "Start of Round:\n" << block;
    cout << "Round Key:\n" << key_list[0];

    block = key_list.add_round_key(block, 0);

    for (int round = 1; round <= 10; round++) {
        cout << "\nRound-" << dec << round << ":\n";
        cout << "Start of Round:\n" << block;
        
        block = box.substitute(block);
        cout << "After SubBytes:\n" << block;

        block = ShiftRows::shift(block);
        cout << "After ShiftRows:\n" << block;

        if (round != 10) {
            block = MixColumns::mix(block);
            cout << "After MixColumns:\n" << block;
        }

        cout << "RoundKey:\n" << key_list[round];
        block = key_list.add_round_key(block, round);
    }
    return block;
}

int main() {
    DataBlock input({
        {0x01, 0x89, 0xFE, 0x76},
        {0x23, 0xAB, 0xDC, 0x54},
        {0x45, 0xCD, 0xBA, 0x32},
        {0x67, 0xEF, 0x98, 0x10}
    });

    DataBlock output = encrypt(input);
    cout << "\nCiphertext:\n" << output;

    return 0;
}