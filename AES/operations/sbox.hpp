#ifndef AES_SBOX
#define AES_SBOX

#include "../math/polynomial.hpp"
#include "../models/datablock.hpp"

class SBox {
protected:
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

    void init() {
        terms = std::vector<std::vector<Polynomial>>(16, std::vector<Polynomial>(16));
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                terms[row][col] = (16 * row + col);
            }
        }
    }

    void invert() {
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                terms[row][col] = terms[row][col].inverse();
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

    static std::ostream& bold_on(std::ostream& os) {
        return os << "\e[1m";
    }

    static std::ostream& bold_off(std::ostream& os) {
        return os << "\e[0m";
    }

    friend std::ostream& operator<< (std::ostream& strm, SBox box) {
        strm << "╔══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╤══╗\n";
        strm << "║  │";
        for (int col = 0; col < 16; col++) {
            strm << std::uppercase << std::hex << " " << bold_on << col << bold_off;
            if (col == 15) {
                strm << "║";
            }
            else {
                strm << "│";
            }
        }
        strm << "\n";
        strm << "╟──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──╢\n";
        for (int row = 0; row < 16; row++) {
            strm << "║";
            strm << std::uppercase << std::hex << " " << bold_on << row << bold_off;
            strm << "│";
            for (int col = 0; col < 16; col++) {
                strm << box.terms[row][col].get_value();
                if (col == 15) {
                    strm << "║";
                }
                else {
                    strm << "│";
                }
            }
            strm << "\n";
            if (row != 15) {
                strm << "╟──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──╢\n";
            }
            else {
                strm << "╚══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╧══╝\n";
            }
        }
        return strm;
    }

    std::vector<std::vector<Polynomial>> terms;

public:
    SBox() {
        init();
    }

    void transform() {
        init();
        invert();
        terms[0][0] = terms[0][0].inverse();
        encrypt_shift();
    }

    Polynomial operator[] (Polynomial poly) {
        uint value = poly.get_value().to_integer();
        return terms[value / 16][value % 16];
    }

    DataBlock substitute(DataBlock block) {
        DataBlock result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result[i][j] = operator[](block[i][j]);
            }
        }
        return result;
    }
};

class ISBox : private SBox {
private:
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

    void decrypt_shift() {
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                terms[row][col] = compute_poly_decrypt(terms[row][col]);
            }
        }
    }

public:
    void inverse_transform() {
        init();
        decrypt_shift();
        invert();
    }

    using SBox::operator[];

    using SBox::substitute;
};

#endif