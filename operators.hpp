#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "./Hex.hpp"
#include "./String.hpp"
#include "./Binary.hpp"
#include "./Decimal.hpp"

namespace operators {
    std::string fixed_xor_encode_hex(Hex hex1, Hex key) {
        std::string xor_binary_string = "";
        std::string hex1Binary = hex1.to_binary();
        std::string keyBinary = key.to_binary();
        for (int i = 0; i < hex1Binary.length(); i++) {
            if (hex1Binary[i] == keyBinary[i]) {
                xor_binary_string += "0";
            } else {
                xor_binary_string += "1";
            }
        }
        Binary encoded;
        encoded.value = xor_binary_string;
        return encoded.to_hex();
    } 

    std::string repeating_xor_encode_string(String message, String key) {
        std::string xor_binary_string = "";
        std::string messageBinary = message.to_binary();
        std::string keyBinary = key.to_binary();
        int keyBinaryLength = keyBinary.length();
        int looped = 0;
        for (int i = 0; i < messageBinary.length(); i++) {
            if(messageBinary[i] == ' ' || keyBinary[i%keyBinaryLength] == ' ') continue;
            if (messageBinary[i] == keyBinary[i%keyBinaryLength]) {
                xor_binary_string += "0";
            } else {
                xor_binary_string += "1";
            }
            looped++;
        }
        Binary encoded;
        encoded.value = xor_binary_string;
        return encoded.to_hex();
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
    int hamming_distance(String str1, String str2) {
        int hammingDistanceCount = 0;
        std::string str1Binary = str1.to_binary();
        std::string str2Binary = str2.to_binary();
        int longestStrBinary = str1Binary.length() < str2Binary.length()
            ? str2Binary.length() : str1Binary.length();
        std::cout << str1Binary << std::endl;
        std::cout << str2Binary << std::endl;
        for (int i = 0; i < longestStrBinary; i++) {
            if (str1Binary[i] == ' ' || str2Binary[i] == ' ') continue;
            if (str1Binary[i] != str2Binary[i]) hammingDistanceCount++;
        }
        return hammingDistanceCount;
    }
}