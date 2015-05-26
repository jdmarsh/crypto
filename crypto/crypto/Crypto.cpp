#include "Crypto.h"

bool validateHexadecimalString(std::string);
bool validateBinaryString(std::string);

std::string cpt::hex2base64(std::string hex) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }
    std::string binary = hex2binary(hex);
    return binary2base64(binary);
}

std::string cpt::hex2binary(std::string hex) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }

    std::string binary;
    for (char character : hex) {
        unsigned decimalValue;
        if (character >= '0' && character <= '9') {
            decimalValue = static_cast<unsigned>(character)-48;
        } else if (character >= 'a' && character <= 'f') {
            decimalValue = static_cast<unsigned>(character)-87;
        } else if (character >= 'A' && character <= 'F') {
            decimalValue = static_cast<unsigned>(character)-55;
        }
        for (int i = 0; i < 4; ++i) {
            if ((decimalValue >> (3 - i)) & 1) {
                binary += '1';
            } else {
                binary += '0';
            }
        }
    }
    return binary;
}

std::string cpt::binary2base64(std::string binary) {
    if (!validateBinaryString(binary)) {
        throw std::string("Invalid binary data provided");
    }

    std::string base64;
    unsigned character = 0;
    for (unsigned base64ChunkIndex = 0; base64ChunkIndex < binary.size(); base64ChunkIndex += 6) {
        for (unsigned bitIndex = 0; bitIndex < 6; ++bitIndex) {
            unsigned index = bitIndex + base64ChunkIndex;
            character = character << 1;
            if (index < binary.size()) {
                if (binary[index] == '1') {
                    ++character;
                }
            }
        }

        if (character < 26) {
            character += 65;
        } else if (character < 52) {
            character += 71;
        } else if (character < 62) {
            character -= 4;
        } else if (character < 63) {
            character -= 19;
        } else {
            character -= 16;
        }
        base64 += static_cast<char>(character);
        character = 0;
    }
    return base64;
}

bool validateHexadecimalString(std::string hex) {
    for (char character : hex) {
        if (!((character >= '0' && character <= '9') || (character >= 'a' &&character <= 'f') || (character >= 'A' && character <= 'F'))) {
            return false;
        }
    }
    return true;
}

bool validateBinaryString(std::string binary) {
    for (char bit : binary) {
        if (!(bit == '0' || bit == '1')) {
            return false;
        }
    }
    return true;
}