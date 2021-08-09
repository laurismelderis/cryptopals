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
    int hamming_distance(Binary bin1, Binary bin2) {
        int hammingDistanceCount = 0;
        for (int i = 0; i < bin1.value.length(); i++) {
            if (bin1.value[i] == ' ' || bin2.value[i] == ' ') continue;
            if (bin1.value[i] != bin2.value[i]) hammingDistanceCount++;
        }
        return hammingDistanceCount;
    }
    int hamming_distance(Decimal dec1, Decimal dec2) {
        int hammingDistanceCount = 0;
        std::string dec1Binary = dec1.to_binary();
        std::string dec2Binary = dec2.to_binary();
        for (int i = 0; i < dec1Binary.length(); i++) {
            if (dec1Binary[i] == ' ' || dec2Binary[i] == ' ') continue;
            if (dec1Binary[i] != dec2Binary[i]) hammingDistanceCount++;
        }
        std::cout << hammingDistanceCount << std::endl;
        return hammingDistanceCount;
    }
    int hamming_distance(String str1, String str2) {
        if (str1.value.length() != str2.value.length()) {
            std::cout << "Strings are not the same length" << std::endl;
            return -1;
        }
        int hammingDistanceCount = 0;
        std::string str1Binary = str1.to_binary();
        std::string str2Binary = str2.to_binary();
        for (int i = 0; i < str1Binary.length(); i++) {
            if (str1Binary[i] == ' ' || str2Binary[i] == ' ') continue;
            if (str1Binary[i] != str2Binary[i]) hammingDistanceCount++;
        }
        return hammingDistanceCount;
    }
    std::string decrypt_xor_hex(Hex encodedXOR) {
        std::string encodedXORStr = encodedXOR.value;
        std::string decryptedXOR = "";

        // Finding the smallest edit distance (Hamming distance)
        const int byteLength = 5;

        int smallestDistance = INT_MAX;
        int totalDistance = 0;
        int distanceCount = 0;

        std::string lastBytes = "";
        for (int i = (encodedXORStr.length()-byteLength*2); i < encodedXORStr.length(); i++) {
            lastBytes += encodedXORStr[i];
        }

        Hex prevPossibleKeyword;
        for (int i = 0; i < byteLength*2; i++) {
            prevPossibleKeyword.value += encodedXOR.value[i];
        }
        std::cout << lastBytes << std::endl;
        Hex possibleKeyword;
        int multiplicator = 1;
        bool exit = false;
        while (prevPossibleKeyword.value != lastBytes && exit == false) {
            int bits = 0;
            for (int i = (byteLength*2)*multiplicator; i < (byteLength*2)*multiplicator+(byteLength*2); i++) {
                if (i > encodedXORStr.length()) {
                    for (int j = bits; j <= byteLength*2; j++) {
                        possibleKeyword.value.insert(0, "0");
                    }
                    exit = true;
                    break;;
                }
                bits++;
                possibleKeyword.value += encodedXOR.value[i];
            }
            Binary possibleKeyword1Binary;
            Binary possibleKeyword2Binary;
            possibleKeyword1Binary.value = prevPossibleKeyword.to_binary();
            possibleKeyword2Binary.value = possibleKeyword.to_binary();

            int distance = hamming_distance(possibleKeyword1Binary, possibleKeyword2Binary);
            totalDistance += distance;
            distanceCount++;

            std::cout << prevPossibleKeyword.value << " " << possibleKeyword1Binary.value << std::endl;
            std::cout << possibleKeyword.value << " " << possibleKeyword2Binary.value << std::endl;
            std::cout << "Distance: " << distance << std::endl;
            if (distance < smallestDistance) {
                smallestDistance = distance;
            }
            prevPossibleKeyword = possibleKeyword;
            possibleKeyword.value = "";
            multiplicator++;
        } 
        std::cout << "Smallest distance: " << smallestDistance << std::endl;
        std::cout << "Total distance: " << totalDistance << std::endl;
        std::cout << "Distance count: " << distanceCount << std::endl;
        float hummingDistanceNAvg = (float)totalDistance/(float)distanceCount/(float)byteLength;
        std::cout << "Average HD: " << hummingDistanceNAvg << std::endl;
        return decryptedXOR;
    }
}