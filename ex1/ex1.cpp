#include <iostream>

/*
       L        a        u        r        i        s       (string) = 32bits
    01001100 01100001 01110101 01110010 01101001 01110011
    010011 000110 000101 110101 011100 100110 100101 110011
      19     6      5      53     28     38     37     51
      T      G      F      1      c      m      l      z    (base64) = 48bits


*/
struct Decimal {
    std::string value;
    std::string to_base64() {
        return "abc";
    }
};

struct Binary {
    std::string value;
    std::string to_decimal() {

    }
    std::string to_base64() {
        std::string base64;
        std::string binary_set;
        for (int i = 0; i < value.length(); i++) {
            binary_set += base64[i];
            if ((i+1) % 6 == 0) {
                Decimal decimal;
                decimal.value = to_decimal();
                base64 += decimal.to_base64();
            }
        }
    }
};

struct Hex {
    std::string value = "";
    std::string to_binary() {
        std::string binary = "";
        for (char c: value) {
            c = std::tolower(c);
            if (c == '0') {
                binary += "0000";
            } else if (c == '1') {
                binary += "0001";
            } else if (c == '2') {
                binary += "0010";
            } else if (c == '3') {
                binary += "0011";
            } else if (c == '4') {
                binary += "0100";
            } else if (c == '5') {
                binary += "0101";
            } else if (c == '6') {
                binary += "0110";
            } else if (c == '7') {
                binary += "0111";
            } else if (c == '8') {
                binary += "1000";
            } else if (c == '9') {
                binary += "1001";
            } else if (c == 'a') {
                binary += "1010";
            } else if (c == 'b') {
                binary += "1011";
            } else if (c == 'c') {
                binary += "1100";
            } else if (c == 'd') {
                binary += "1101";
            } else if (c == 'e') {
                binary += "1110";
            } else if (c == 'f') {
                binary += "1111";
            }
        }
        return binary;
    }
    std::string to_base64() {
        Binary binary;
        binary.value = to_binary();
        return binary.to_base64();
    }
};

int main() {
    Hex hex;
    hex.value = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::cout << hex.to_base64() << std::endl;
    return 0;
}