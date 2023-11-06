#ifndef AES_POLYNOMIAL
#define AES_POLYNOMIAL

#include "bitlist.hpp"
#include "hexval.hpp"

#define MOD "100011011"

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

    std::pair<Polynomial, Polynomial> extended_euclid(Polynomial poly, Polynomial mod) {
        if (mod == 0) {
            return {1, 0};
        }
        auto [prev_x, prev_y] = extended_euclid(mod, poly % mod);
        Polynomial curr_x = prev_y;
        Polynomial curr_y = prev_x - ((poly / mod) * prev_y);
        return {curr_x, curr_y};
    }

    std::pair<Polynomial, Polynomial> long_division(Polynomial dividend, Polynomial divisor) {
        Polynomial quotient;
        while (dividend >= divisor) {
            int multiplier = 1;
            int n = (dividend.coefficients.size() - divisor.coefficients.size());
            for (int i = 0; i < n; i++) {
                multiplier <<= 1;
            }
            quotient += multiplier;
            dividend -= (divisor << n);
        }
        dividend.update_value();
        quotient.update_value();
        return {quotient, dividend};
    }

    friend std::ostream& operator<< (std::ostream& strm, Polynomial poly) {
        std::vector<std::string> terms;
        for (int i = poly.size() - 1; i > 0; i--) {
            if (poly.coefficients[i] == 1) {
                if (i == 1) {
                    terms.push_back("x");
                }
                else {
                    terms.push_back("x^" + std::to_string(i));
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
        for (int i = 0; i < n - 1; i++) {
            strm << (terms[i] + " + ");
        }
        strm << terms[n - 1];
        return strm;
    }

public:
    BitList coefficients;

    Hex_Value binary;

    static Polynomial* mod;

    Polynomial() {}

    Polynomial(uint bits) {
        coefficients = bits;
        binary = bits;
    }

    Polynomial(const std::string& bits) {
        coefficients = bits;
        update_value();
    }

    Hex_Value get_value() {
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

    void operator= (const std::string& bits) {
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
        result.update_value();
        return result;
    }

    void operator<<= (int n) {
        operator= (operator<< (n));
    }

    Polynomial operator+ (Polynomial poly) {
        Polynomial result;
        size_t size = std::max(coefficients.size(), poly.coefficients.size());
        for (int i = 0; i < size; i++) {
            result.coefficients.add(coefficients[i] + poly.coefficients[i]);
        }
        result.trim();
        result.update_value();
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
        product %= (*(Polynomial::mod));
        product.update_value();
        return product;
    }

    void operator*= (Polynomial poly) {
        operator= (operator* (poly));
    }

    Polynomial operator% (Polynomial poly) {
        if (poly == 0 || poly.coefficients.size() == 0) {
            throw std::runtime_error("Math error: Cannot divide by zero");
        }
        if (operator< (poly)) {
            return Polynomial(*this);
        }
        Polynomial dividend = *this;
        Polynomial divisor = poly;
        auto [quotient, remainder] = long_division(dividend, divisor);
        return remainder;
    }

    void operator%= (Polynomial poly) {
        operator= (operator% (poly));
    }

    Polynomial operator/ (Polynomial poly) {
        if (poly == 0 || poly.coefficients.size() == 0) {
            throw std::runtime_error("Math error: Cannot divide by zero");
        }
        if (operator< (poly)) {
            return 0;
        }
        Polynomial dividend = *this;
        Polynomial divisor = poly;
        auto [quotient, remainder] = long_division(dividend, divisor);
        return quotient;
    }

    void operator/= (Polynomial poly) {
        operator= (operator/ (poly));
    }

    Polynomial inverse() {
        trim();
        auto [x, y] = extended_euclid(*this, *(Polynomial::mod));
        x.update_value();
        return x;
    }

    Polynomial operator^ (int p) {
        if (operator== (0)) {
            return 0;
        }
        Polynomial result(1);
        if (p >= 0) {
            for (int i = 0; i < p; i++) {
                result *= (*this);
            }
            result.update_value();
            return result;
        }
        Polynomial inv = inverse();
        for (int i = 0; i < (-p); i++) {
            result *= inv;
        }
        result.update_value();
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

Polynomial* Polynomial::mod = new Polynomial(MOD);

#endif