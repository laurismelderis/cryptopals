#pragma once
#include <string>

class Binary {
private:
public:
    std::string value;
    std::string to_decimal() {
        int decimal = 0;
        int valueLength = value.length();
        int bits = 0;
        for (int i = valueLength-1; i >= 0; i--) {
            decimal += pow(2, i)*((int)value[valueLength-1-i]-48);
        }
        return std::to_string(decimal);
    }
    std::string to_hex() {
        std::string hex = "";
        std::string temp_bin = "";
        for (int i = 0; i < value.length(); i++) {
            temp_bin += value[i];
            if ((i+1) % 4 == 0) {
                if (temp_bin == "0000") hex += "0";
                else if (temp_bin == "0001") hex += "1";
                else if (temp_bin == "0010") hex += "2";
                else if (temp_bin == "0011") hex += "3";
                else if (temp_bin == "0100") hex += "4";
                else if (temp_bin == "0101") hex += "5";
                else if (temp_bin == "0110") hex += "6";
                else if (temp_bin == "0111") hex += "7";
                else if (temp_bin == "1000") hex += "8";
                else if (temp_bin == "1001") hex += "9";
                else if (temp_bin == "1010") hex += "a";
                else if (temp_bin == "1011") hex += "b";
                else if (temp_bin == "1100") hex += "c";
                else if (temp_bin == "1101") hex += "d";
                else if (temp_bin == "1110") hex += "e";
                else if (temp_bin == "1111") hex += "f";
                temp_bin = "";
            }
        }
        return hex;
    }
};