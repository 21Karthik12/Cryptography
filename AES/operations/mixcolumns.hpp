#ifndef AES_MIX_COLUMNS
#define AES_MIX_COLUMNS

#include "../models/datablock.hpp"
#include "../math/polynomial.hpp"

class MixColumns {
public:
    static Matrix multiplier;
    
    static Matrix inverse_multiplier;

    static DataBlock mix(DataBlock block) {
        return (multiplier * block);
    }

    static DataBlock inverse_mix(DataBlock block) {
        return (inverse_multiplier * block);
    }
};

Matrix MixColumns::multiplier = Matrix({
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
});

Matrix MixColumns::inverse_multiplier = Matrix({
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E}
});

#endif