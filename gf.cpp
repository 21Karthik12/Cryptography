#include <bits/stdc++.h>

using namespace std;

class Polynomial {
private:
    void trim() {
        for (int i = coefficients.size() - 1; i > 0; i--) {
            if (coefficients[i] == 1) {
                return;
            }
            coefficients.pop();
        }
    }
    void extended_euclid(Polynomial poly, Polynomial mod, Polynomial& x, Polynomial& y) {
        if (mod == Polynomial(0)) {
            x = Polynomial(1);
            y = Polynomial(0);
            return;
        }
        Polynomial prev_x, prev_y;
        extended_euclid(mod, poly % mod, prev_x, prev_y);
        x = prev_y;
        y = prev_x - ((poly / mod) * prev_y);
    }
    uint binary;
public:
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
        Bit operator+ (int val) {
            return Bit(value ^ val);
        }
        Bit operator+ (const Bit& bit) {
            return Bit(value ^ bit.value);
        }
        void operator+= (int val) {
            operator= (operator+ (val));
        }
        void operator+= (const Bit& bit) {
            operator= (operator+ (bit));
        }
        Bit operator- (int val) {
            return operator+ (val);
        }
        Bit operator- (const Bit& bit) {
            return operator+ (bit);
        }
        void operator-= (int val) {
            operator= (operator- (val));
        }
        void operator-= (const Bit& bit) {
            operator= (operator- (bit));
        }
        Bit operator* (int val) {
            return Bit(value & val);
        }
        Bit operator* (const Bit& bit) {
            return Bit(value & bit.value);
        }
        bool operator== (int val) {
            return (value == val);
        }
        bool operator== (const Bit& bit) {
            return (value == bit.value);
        }
        bool operator!= (int val) {
            return (value != val);
        }
        bool operator!= (const Bit& bit) {
            return !operator==(bit);
        }
    };
    class BitList {
    private:
        vector<Bit> bits;
    public:
        BitList() {}
        BitList(uint bitstring) {
            do {
                bits.emplace_back(bitstring & 1);
                bitstring >>= 1;
            } while (bitstring > 0);
        }
        BitList(const string& bitstring) {
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
        void operator= (const string& bitstring) {
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
        void add(int val) {
            add(Bit(val));
        }
        void add_front(Bit bit) {
            bits.insert(bits.begin(), bit);
        }
        void add_front(int val) {
            add_front(Bit(val));
        }
        size_t size() {
            return bits.size();
        }
        void pop() {
            bits.pop_back();
        }
        void left_shift() {
            bits.insert(bits.begin(), Bit(0));
        }
    };
    BitList coefficients;
    static Polynomial* mod;
    Polynomial() {}
    Polynomial(uint bits) {
        coefficients = bits;
        binary = bits;
    }
    Polynomial(const string& bits) {
        coefficients = bits;
        update_value();
    }
    uint get_value() {
        return binary;
    }
    void update_value() {
        int mul = 1;
        binary = 0;
        for (int i = 0, n = coefficients.size(); i < n; i++) {
            if (coefficients[i] == 1) {
                binary += mul;
            }
            mul <<= 1;
        }
    }
    void operator= (uint bits) {
        coefficients = bits;
        binary = bits;
    }
    void operator= (const string& bits) {
        coefficients = bits;
        update_value();
    }
    void operator= (Polynomial poly) {
        coefficients = poly.coefficients;
        update_value();
    }
    bool operator== (Polynomial poly) {
        return (coefficients == poly.coefficients);
    }
    bool operator!= (Polynomial poly) {
        return (coefficients != poly.coefficients);
    }
    bool operator> (Polynomial poly) {
        Polynomial zero(0);
        if (operator!= (zero) && poly == zero) {
            return true;
        }
        return (coefficients.size() > poly.coefficients.size());
    }
    bool operator< (Polynomial poly) {
        Polynomial zero(0);
        if (operator== (zero) && poly != zero) {
            return true;
        }
        return (coefficients.size() < poly.coefficients.size());
    }
    bool operator>= (Polynomial poly) {
        return !(operator< (poly));
    }
    bool operator<= (Polynomial poly) {
        return !(operator> (poly));
    }
    Polynomial operator<< (int n) {
        Polynomial result = *this;
        for (int i = 0; i < n; i++) {
            result.coefficients.left_shift();
        }
        return result;
    }
    void operator<<= (int n) {
        operator= (operator<< (n));
    }
    Polynomial operator+ (Polynomial poly) {
        Polynomial result;
        size_t size = max(coefficients.size(), poly.coefficients.size());
        for (int i = 0; i < size; i++) {
            result.coefficients.add(coefficients[i] + poly.coefficients[i]);
        }
        result.trim();
        return result;
    }
    void operator+= (Polynomial poly) {
        operator= (operator+ (poly));
    }
    Polynomial operator- (Polynomial poly) {
        return operator+ (poly);
    }
    void operator-= (Polynomial poly) {
        operator= (operator- (poly));
    }
    Polynomial operator* (Polynomial poly) {
        Polynomial product(0);
        for (int i = 0, n = coefficients.size(); i < n; i++) {
            if (coefficients[i] == 1) {
                product += (poly << i);
            }
        }
        return product % (*(Polynomial::mod));
    }
    void operator*= (Polynomial poly) {
        operator= (operator* (poly));
    }
    Polynomial operator% (Polynomial poly) {
        if (poly == Polynomial(0)) {
            throw runtime_error("Math error: Cannot divide by zero");
        }
        if (operator< (poly)) {
            return Polynomial(*this);
        }
        Polynomial dividend = *this;
        Polynomial divisor = poly;
        Polynomial quotient;
        while (dividend >= divisor) {
            int multiplier = 1;
            int n = (dividend.coefficients.size() - divisor.coefficients.size());
            for (int i = 0; i < n; i++) {
                multiplier <<= 1;
            }
            quotient += Polynomial(multiplier);
            dividend -= (divisor << n);
        }
        return dividend;
    }
    void operator%= (Polynomial poly) {
        operator= (operator% (poly));
    }
    Polynomial operator/ (Polynomial poly) {
        if (poly == Polynomial(0)) {
            throw runtime_error("Math error: Cannot divide by zero");
        }
        if (operator< (poly)) {
            return Polynomial(0);
        }
        Polynomial dividend = *this;
        Polynomial divisor = poly;
        Polynomial quotient;
        while (dividend >= divisor) {
            int multiplier = 1;
            int n = (dividend.coefficients.size() - divisor.coefficients.size());
            for (int i = 0; i < n; i++) {
                multiplier <<= 1;
            }
            quotient += Polynomial(multiplier);
            dividend -= (divisor << n);
        }
        return quotient;
    }
    void operator/= (Polynomial poly) {
        operator= (operator/ (poly));
    }
    Polynomial inverse() {
        trim();
        Polynomial x, y;
        extended_euclid(*this, *(Polynomial::mod), x, y);
        return x;
    }
    Polynomial operator^ (int p) {
        if (operator== (Polynomial(0))) {
            return Polynomial(0);
        }
        Polynomial result(1);
        if (p >= 0) {
            for (int i = 0; i < p; i++) {
                result *= (*this);
            }
            return result;
        }
        Polynomial inv = inverse();
        for (int i = 0; i < (-p); i++) {
            result *= inv;
        }
        return result;
    }
    void operator^= (int p) {
        operator= (operator^ (p));
    }
    size_t size() {
        trim();
        return coefficients.size();
    }
};

ostream& operator<< (ostream& strm, Polynomial poly) {
    vector<string> terms;
    for (int i = poly.size() - 1; i > 0; i--) {
        if (poly.coefficients[i] == 1) {
            if (i == 1) {
                terms.push_back("x");
            }
            else {
                terms.push_back("x^" + to_string(i));
            }
        }
    }
    if (poly.coefficients[0] == 1) {
        terms.push_back("1");
    }
    else if (terms.size() == 0) {
        terms.push_back("0");
    }
    int n = terms.size();
    string result;
    for (int i = 0; i < n - 1; i++) {
        result += (terms[i] + " + ");
    }
    result += terms[n - 1];
    return strm << result;
}

Polynomial* Polynomial::mod = new Polynomial("100011011");

class S_Box {
private:
    using Bit = Polynomial::Bit;
    Polynomial compute_poly_encrypt(Polynomial poly) {
        Polynomial result = poly;
        Polynomial offset(0x63);
        Bit new_value = poly.coefficients[0];
        for (int i = 4; i < 8; i++) {
            new_value += poly.coefficients[i];
        }
        result.coefficients[0] = new_value + offset.coefficients[0];
        for (int i = 1; i < 8; i++) {
            new_value += (poly.coefficients[i] + poly.coefficients[(i + 3) % 8]);
            result.coefficients[i] = (new_value + offset.coefficients[i]);
        }
        result.update_value();
        return result;
    }
    Polynomial compute_poly_decrypt(Polynomial poly) {
        Polynomial result = poly;
        Polynomial offset(0x05);
        for (int i = 0; i < 8; i++) {
            Bit new_value = poly.coefficients[(i + 2) % 8] + 
                            poly.coefficients[(i + 5) % 8] +
                            poly.coefficients[(i + 7) % 8];
            result.coefficients[i] = (new_value + offset.coefficients[i]);
        }
        result.update_value();
        return result;
    }
    void init() {
        terms = vector<vector<Polynomial>>(16, vector<Polynomial>(16));
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                terms[row][col] = (16 * row + col);
            }
        }
    }
    void invert() {
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                if ((row + col) != 0) {
                    terms[row][col] = terms[row][col].inverse();
                }
            }
        }
    }
    void encrypt_shift() {
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                terms[row][col] = compute_poly_encrypt(terms[row][col]);
            }
        }
    }
    void decrypt_shift() {
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                terms[row][col] = compute_poly_decrypt(terms[row][col]);
            }
        }
    }
    vector<vector<Polynomial>> terms;
public:
    void transform() {
        init();
        invert();
        encrypt_shift();
    }
    void inverse_transform() {
        init();
        decrypt_shift();
        terms[0][0] = terms[0][0].inverse();
        invert();
    }
    void display() {
        cout << "┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐\n";
        cout << "│  │";
        for (int col = 0; col < 16; col++) {
            cout << uppercase << hex << " " << col;
            cout << "│";
        }
        cout << "\n";
        cout << "├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤\n";
        for (int row = 0; row < 16; row++) {
            cout << "│";
            cout << uppercase << hex << " " << row;
            cout << "│";
            for (int col = 0; col < 16; col++) {
                cout << setw(2) << setfill('0') << uppercase << hex << terms[row][col].get_value();
                cout << "│";
            }
            cout << "\n";
            if (row != 15) {
                cout << "├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤\n";
            }
            else {
                cout << "└──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘\n";
            }
        }
    }
};

int main() {
    S_Box box;
    
    box.transform();
    cout << "\nS-Box:\n";
    box.display();
    
    box.inverse_transform();
    cout << "\nInverse S-Box:\n";
    box.display();

    return 0;
}