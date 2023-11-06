#ifndef AES_HEXVAL
#define AES_HEXVAL

#include <iomanip>

class Hex_Value {
private:
    uint value;

    friend std::ostream& operator<< (std::ostream& strm, const Hex_Value& v) {
        strm << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << v.value;
        return strm;
    }

public:
    Hex_Value (uint v) : value(v) {}

    Hex_Value () : value(0) {}

    uint to_integer() {
        return value;
    }

    void operator= (Hex_Value v) {
        value = v.value;
    }

    void operator= (uint v) {
        value = v;
    }

    Hex_Value operator+ (Hex_Value v) {
        return (value + v.value);
    }

    void operator+= (Hex_Value v) {
        operator= (operator+ (v));
    }

    Hex_Value operator- (Hex_Value v) {
        return (value - v.value);
    }

    void operator-= (Hex_Value v) {
        operator= (operator- (v));
    }
};

#endif