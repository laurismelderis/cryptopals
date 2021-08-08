#include <iostream>

#include "../../Hex.hpp"
#include "../../String.hpp"
#include "../../operators.hpp"

/* Example
    '1' = 110001
    '6' = 110110
    xor = 000111
*/


int main() {
    Hex hex1, hex2;
    hex1.value = "1c0111001f010100061a024b53535009181c";
    hex2.value = "686974207468652062756c6c277320657965";
    std::cout << operators::xor_hex(hex1, hex2) << std::endl;
    return 0;
}