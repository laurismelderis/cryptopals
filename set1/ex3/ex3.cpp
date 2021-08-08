#include <iostream>

#include "../../Hex.hpp"
#include "../../operators.hpp"

int main() {
    // Secret message
    // Cooking MC's like a pound of bacon

    Hex encoded_hex;
    encoded_hex.value = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::vector<std::string> possibleMessages = operators::single_byte_xor_decode_hex_guesser(encoded_hex);
    for (std::string message: possibleMessages){
        std::cout << message << std::endl;
    }
    return 0;
}