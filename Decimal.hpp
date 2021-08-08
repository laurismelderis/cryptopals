#pragma once
#include <string>

class Decimal {
private:
public:
    std::string value;
    char to_base64() {
        std::string base64Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        return base64Characters[stoi(value)];
    }
    std::string to_binary() {
        std::string binary = "";
        
        int quotient = stoi(value) / 2;
        int remainder = stoi(value) % 2;
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
};