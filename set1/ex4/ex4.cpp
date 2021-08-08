#include <iostream>

#include "../../Hex.hpp"
#include "../../operators.hpp"

int main() {
    // Secret message
    // Now that the party is jumping

    std::vector<std::string> rows;
    std::string row = "";
    for (int i = 0; i < 327; i++) {
        std::cin >> row;
        rows.push_back(row);
    }
    
    Hex encoded_hex;
    for (std::string encodedMessage: rows) {
        encoded_hex.value = encodedMessage;
        std::vector<std::string> possibleMessages = operators::single_byte_xor_decode_hex_guesser(encoded_hex);
        for (std::string message: possibleMessages){
            std::cout << message << std::endl;
        }
    }
    return 0;
}