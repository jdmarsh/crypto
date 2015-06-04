#include "Crypto.h"

bool validateHexadecimalString(std::string);
bool validateBinaryString(std::string);
unsigned short getPlainTextScore(std::string);

std::string cpt::hexXor(std::string& hexA, std::string& hexB) {
    if (hexA.size() != hexB.size()) {
        throw std::string("hexadecimal values must be of equal length");
    }
    if (!validateHexadecimalString(hexA) || !validateHexadecimalString(hexB)) {
        throw std::string("Invalid hexadecimal data provided");
    }

    std::string binaryA = hex2binary(hexA);
    std::string binaryB = hex2binary(hexB);

    if (binaryA.size() % 8 > 0) {
        binaryA = "0000" + binaryA;
    }
    
    std::string binaryXor;
    for (unsigned index = 0; index < binaryA.size(); ++index) {
        bool bitA = binaryA[index] == '1';
        bool bitB = binaryB[index] == '1';
        if (bitA ^ bitB) {
            binaryXor += '1';
        } else {
            binaryXor += '0';
        }
    }
    return binary2hex(binaryXor);
}
#include <iostream>
std::string cpt::hexXorSingleByte(std::string& hex, std::string& xorByte) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }
    if (!validateHexadecimalString(xorByte) || !(xorByte.size() <= 2)) {
        throw std::string("Invalid byte key provided");
    }

    std::string repeatedXorByte;
    for (unsigned index = 0; index < hex.size(); index += 2) {
        if (xorByte.size() == 0) {
            repeatedXorByte += "00";
        } else if (xorByte.size() == 1) {
            repeatedXorByte += "0";
        }
        repeatedXorByte += xorByte;
    }

    return hexXor(hex, repeatedXorByte);
}

std::string cpt::decodeSingleByteCipher(std::string& hex) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }

    unsigned short scores[256];
    for (unsigned i = 0; i < 256; ++i) {
        std::string hexByte = binary2hex(decimal2binary(i));
        std::string decodedCipher = hexXorSingleByte(hex, hexByte);
        scores[i] = getPlainTextScore(decodedCipher);
    }
    unsigned highestScore = 0;
    unsigned highestScoreIndex = 0;
    for (unsigned i = 0; i < 256; ++i) {
        if (scores[i] > highestScore) {
            highestScore = scores[i];
            highestScoreIndex = i;
        }
    }
    std::string hexByte = binary2hex(decimal2binary(highestScoreIndex));
    return hexXorSingleByte(hex, hexByte);
}

std::string cpt::repeatingKeyXor(std::string& message, std::string& key) {
    std::string encodedMessage;
    for (unsigned i = 0; i < message.size(); ++i) {
        encodedMessage += message[i] ^ key[i % key.size()];
    }
    return ascii2hex(encodedMessage);
}

std::string cpt::ascii2hex(std::string& message) {
    std::string hex;
    for (unsigned i = 0; i < message.size(); ++i) {
        unsigned lByte = message[i] >> 4;
        unsigned rByte = message[i] & 0xf;
        hex += decimal2hex(lByte);
        hex += decimal2hex(rByte);
    }
    return hex;
}

std::string cpt::hex2base64(std::string& hex) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }
    std::string binary = hex2binary(hex);
    return binary2base64(binary);
}

std::string cpt::hex2binary(std::string& hex) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }

    std::string binary;
    for (char character : hex) {
        //Convert from ASCII to decimal
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

std::string cpt::decimal2hex(unsigned value) {
    std::string hex;
    do {
        unsigned character = value & 0xf;
        if (character < 10) {
            character += 48;
        } else {
            character += 87;
        }
        hex += static_cast<char>(character);
        value = value >> 4;
    } while (value > 0);
    return hex;
}

std::string cpt::decimal2binary(unsigned value) {
    std::string binary;

    do {
        if (value & 1) {
            binary = '1' + binary;
        } else {
            binary = '0' + binary;
        }
        value = value >> 1;
    } while (value > 0);

    return binary;
}

unsigned cpt::binary2decimal(std::string& binary) {
    if (!validateBinaryString(binary)) {
        throw std::string("Invalid binary data provided");
    }

    unsigned value = 0;
    for (char bit : binary) {
        value = value << 1;
        if (bit == '1') {
            ++value;
        }
    }
    return value;
}

std::string cpt::binary2hex(std::string& binary) {
    if (!validateBinaryString(binary)) {
        throw std::string("Invalid binary data provided");
    }

    std::string hex;
    unsigned padding = (4 - (binary.size() % 4)) % 4;
    for (unsigned bitChunkIndex = 0; bitChunkIndex < binary.size() + padding; bitChunkIndex += 4) {
        unsigned character = 0;
        for (unsigned bitIndex = 0; bitIndex < 4; ++bitIndex) {
            character = character << 1;
            if (bitChunkIndex + bitIndex >= padding && binary[bitChunkIndex + bitIndex - padding] == '1') {
                ++character;
            }
        }
        //Convert from decimal to ASCII
        if (character < 10) {
            character += 48;
        } else {
            character += 87;
        }
        hex += static_cast<char>(character);
    }
    return hex;
}

std::string cpt::binary2base64(std::string& binary) {
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

        //Convert from ASCII to base64 representation
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

unsigned short cpt::getPlainTextScore(std::string hex) {
    if (!validateHexadecimalString(hex)) {
        throw std::string("Invalid hexadecimal data provided");
    }

    //Force byte alignment for hexadecimal data
    if (hex.size() % 2 != 0) {
        hex = "0" + hex;
    }

    unsigned short score = 0;
    for (unsigned index = 0; index < hex.size(); index += 2) {
        std::string binary = cpt::hex2binary(hex.substr(index, 2));
        char character = static_cast<char>(cpt::binary2decimal(binary));
        if (character >= 'a' && character <= 'z') {
            score += 500;
        } else if (character == ' ') {
            score += 150;
        } else if (character >= 'A' && character <= 'Z') {
            score += 100;
        } else if (character >= '0' && character <= '9') {
            score += 50;
        }
    }
    return score;
}