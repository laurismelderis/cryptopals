#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "./Hex.hpp"
#include "./Binary.hpp"
#include "./Decimal.hpp"

namespace operators {
    std::string fixed_xor_encode_hex(Hex hex1, Hex hex2) {
        std::string xor_binary_string = "";
        std::string hex1Binary = hex1.to_binary();
        std::string hex2Binary = hex2.to_binary();
        for (int i = 0; i < hex1Binary.length(); i++) {
            if (hex1Binary[i] == hex2Binary[i]) {
                xor_binary_string += "0";
            } else {
                xor_binary_string += "1";
            }
        }
        Binary result;
        result.value = xor_binary_string;
        return result.to_hex();
    }

    bool hasNonSense(std::string text) {
        int score = 0;
        char normalLetters[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3',
            '4', '5', '6', '7', '8', '9'
        };
        char notNormalLetters[] = {
            '[', ']', '`', '/', '\\', '.', '+', '(',
            ')', ',', '*', '{', '}', '!', '?',
            '#', '$', '^', '&', '@'
        };
        for (char c: text) {
            for(char n: normalLetters) {
                if (c == n) {
                    score++;
                    break;
                }
            }
            for (char nn: notNormalLetters) {
                if (c == nn) {
                    score--;
                    break;
                }
            }
        }
        return score < 15;
    }

    std::vector<std::string> single_byte_xor_decode_hex_guesser(Hex encodedMessage) {
        std::vector<std::string> possibleMessages;
        int encodedMessageLength = encodedMessage.value.length();
        std::string guess = "";
        for (int i = 0; i < 256; i++) {
            Decimal dec;
            dec.value = std::to_string(i);
            Binary bin;
            bin.value = dec.to_binary();
            Hex possibleKey;
            possibleKey.value = bin.to_hex();
            std::string postfix = possibleKey.value;
            while (possibleKey.value.length() < encodedMessageLength) {
                possibleKey.value += postfix;
            }
            Hex possibleMessage;
            possibleMessage.value = fixed_xor_encode_hex(encodedMessage, possibleKey);
            if (!hasNonSense(possibleMessage.to_string())) {
                possibleMessages.push_back(possibleMessage.to_string());
            }
        }
        return possibleMessages;
    }
}