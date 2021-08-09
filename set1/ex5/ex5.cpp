#include <iostream>

#include "../../Hex.hpp"
#include "../../String.hpp"
#include "../../operators.hpp"

int main() {
    String message, repatingKey;
    message.value = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
    repatingKey.value = "ICE";
    std::cout << operators::repeating_xor_encode_string(message, repatingKey) << std::endl;

    return 0;
}