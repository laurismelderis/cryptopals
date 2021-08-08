#include <iostream>

#include "../../Hex.hpp"
#include "../../operators.hpp"

int main() {
    Hex hex1, hex2;
    hex1.value = "1c0111001f010100061a024b53535009181c";
    hex2.value = "686974207468652062756c6c277320657965";
    std::cout << operators::fixed_xor_encode_hex(hex1, hex2) << std::endl;
    return 0;
}