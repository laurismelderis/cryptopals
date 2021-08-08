#pragma once
#include <string>
#include <cmath>

#include "./base64.hpp"

class Hex {
private:
public:
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

    int to_decimal(std::string hex) {
        int decimal = 0;
        int valueLength = hex.length();
        for (int i = valueLength-1; i >= 0; i--) {
            char singelHex = hex[valueLength-1-i];
            int singelHexValue = (int)hex[valueLength-1-i]-48;
            if (std::tolower(singelHex) == 'a') singelHexValue = 10;
            else if (std::tolower(singelHex) == 'b') singelHexValue = 11;
            else if (std::tolower(singelHex) == 'c') singelHexValue = 12;
            else if (std::tolower(singelHex) == 'd') singelHexValue = 13;
            else if (std::tolower(singelHex) == 'e') singelHexValue = 14;
            else if (std::tolower(singelHex) == 'f') singelHexValue = 15;

            decimal += singelHexValue * pow(16, i);
        }
        return decimal;
    }

    std::string to_string() {
        std::string str = "";
        std::string pair = "";
        int pairValue = 0;
        for (int i = 0; i < value.length(); i++) {
            pair += value[i];
            if ((i+1) % 2 == 0) {
                pairValue = to_decimal(pair);
                str += (char)pairValue;
                pair = "";
            }

        }
        if (value.length() % 2 == 1) {
            int hexValue = to_decimal(std::to_string(value[value.length() - 1]));
            str += (char)hexValue;
        }
        return str;
    }

    std::string to_base64() {
        return Base64::Encode(to_string());
    }
};