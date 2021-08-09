#include <iostream>

#include "../../Hex.hpp"
#include "../../String.hpp"
#include "../../operators.hpp"
#include "../../Base64.hpp"

int main() {
    // String str1, str2;
    // str1.value = "fu";
    // str2.value = "us";
    // std::cout << "HM distance: " << operators::hamming_distance(str1, str2) << std::endl;

    // std::string base64EncodedMessage = "HUIfTQsPAh9PE048GmllH0kcDk4TAQsHThsBFkU2AB4BSWQgVB0dQzNTTmVS";
    // std::string base64DecodedMessage = Base64::Decode(base64EncodedMessage);
    // std::vector<Base64> messages;
    // for (int i = 0; i < 64; i++) {
    //     std::cin >> message.value;
    //     messages.push_back(message);
    // }
    String message;
    message.value = "fuse fuel for falling flocks";
    String key;
    key.value = "few";
    std::string XORed = operators::repeating_xor_encode_string(message, key);
    std::cout << XORed << std::endl;
    Hex xoredHex;
    xoredHex.value = XORed;
    std::cout << operators::decrypt_xor_hex(xoredHex) << std::endl;
    // std::cout << operators::decrypt_xor(base64DecodedMessage) << std::endl;

    return 0;
}