#pragma once
#include <string>

#include "./base64.hpp"

class String {
private:
public:
    std::string value;
    std::string to_base64() {
        return Base64::Encode(value);
    }
};