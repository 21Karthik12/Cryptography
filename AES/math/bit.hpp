#ifndef AES_BIT
#define AES_BIT

class Bit {
public:
    int value;

    Bit(int val) : value(val) {}

    Bit(const Bit& bit) : value(bit.value) {}

    Bit() : value(0) {}

    void operator= (int val) {
        value = val;
    }

    void operator= (const Bit& bit) {
        value = bit.value;
    }

    Bit operator+ (const Bit& bit) {
        return Bit(value ^ bit.value);
    }

    void operator+= (const Bit& bit) {
        operator= (operator+ (bit));
    }

    Bit operator- (const Bit& bit) {
        return operator+ (bit);
    }

    void operator-= (const Bit& bit) {
        operator= (operator- (bit));
    }

    Bit operator* (const Bit& bit) {
        return Bit(value & bit.value);
    }

    void operator*= (const Bit& bit) {
        operator= (operator* (bit));
    }

    bool operator== (const Bit& bit) {
        return (value == bit.value);
    }

    bool operator!= (const Bit& bit) {
        return !operator==(bit);
    }
};

#endif