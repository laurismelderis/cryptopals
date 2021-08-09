#include <iostream>

#include "../../Hex.hpp"
#include "../../String.hpp"
#include "../../operators.hpp"

int main() {
    String str1, str2;
    str1.value = "this is a test";
    str2.value = "wokka wokka!!!";
    std::cout << operators::hamming_distance(str1, str2) << std::endl;

    return 0;
}