#pragma once
#include <string>

class Binary {
    std::string value;
    std::string to_decimal() {
        int decimal = 0;
        int valueLength = value.length();
        for (int i = valueLength-1; i >= 0; i--) {
            decimal += pow(2, i)*((int)value[valueLength-1-i]-48);
        }
        return std::to_string(decimal);
    }
};