#pragma once
#include <string>

#include "./base64.hpp"

class String {
private:
public:
    std::string value;
    std::string to_binary(int val) {
        std::string binary = "";
        
        int quotient = val / 2;
        int remainder = val % 2;
        int bits = 1;
        binary += std::to_string(remainder);

        while(true) {
            if (quotient == 0) break;
            remainder = quotient % 2;
            quotient /= 2;
            binary += std::to_string(remainder);
            bits++;
        }

        while (bits < 8) {
            binary += "0";
            bits++;
        }

        std::string reversedBinary = "";

        for (int i = binary.length()-1; i >= 0; i--) {
            reversedBinary += binary[i];
        }

        return reversedBinary;
    }
    std::string to_binary() {
        std::string binary = "";
        for (int i = 0; i < value.length(); i++) {
            int charValue = value[i];
            binary += to_binary(charValue) + " ";
        }
        return binary;
    }
    std::string to_base64() {
        return Base64::Encode(value);
    }
};