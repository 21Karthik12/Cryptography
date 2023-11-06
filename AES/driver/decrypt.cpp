#include <bits/stdc++.h>

#include "../operations/sbox.hpp"
#include "../operations/shiftrows.hpp"
#include "../operations/mixcolumns.hpp"
#include "../operations/addroundkey.hpp"

using namespace std;

DataBlock decrypt(DataBlock input) {
    cout << "Encrypting...\n";

    ISBox ibox;
    ibox.inverse_transform();
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
    cout << "Round Key:\n" << key_list[10];

    block = key_list.add_round_key(block, 10);
    cout << "After AddRoundKey:\n" << block;

    for (int round = 1; round <= 10; round++) {
        cout << "\nRound-" << dec << round << ":\n";

        block = ShiftRows::inverse_shift(block);
        cout << "After Inverse ShiftRows:\n" << block;
        
        block = ibox.substitute(block);
        cout << "After Inverse SubBytes:\n" << block;

        cout << "RoundKey:\n" << key_list[10 - round];
        block = key_list.add_round_key(block, 10 - round);
        cout << "After AddRoundKey:\n" << block;

        if (round != 10) {
            block = MixColumns::inverse_mix(block);
            cout << "After Inverse MixColumns:\n" << block;
        }
    }
    return block;
}

int main() {
    DataBlock input({
        {0xFF, 0x08, 0x69, 0x64},
        {0x0B, 0x53, 0x34, 0x14},
        {0x84, 0xBF, 0xAB, 0x8F},
        {0x4A, 0x7C, 0x43, 0xB9}
    });

    DataBlock output = decrypt(input);
    cout << "\nPlaintext:\n" << output;

    return 0;
}