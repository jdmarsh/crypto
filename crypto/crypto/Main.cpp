#include "Main.h"

int main() {
    try {
        std::cout << "Set 1 Challenge 1" << std::endl;
        std::cout << cpt::hex2base64(std::string("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")) << std::endl;

        std::cout << "Set 1 Challenge 2" << std::endl;
        std::cout << cpt::hexXor(std::string("1c0111001f010100061a024b53535009181c"),std::string("686974207468652062756c6c277320657965")) << std::endl;

        std::cout << "Set 1 Challenge 3" << std::endl;
        std::string hexMessage = cpt::decodeSingleByteCipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
        std::string binaryMessage = cpt::hex2binary(hexMessage);
        for (unsigned i = 0; i < binaryMessage.size(); i += 8) {
            std::cout << static_cast<char>(cpt::binary2decimal(binaryMessage.substr(i, 8)));
        }
    } catch (std::string e) {
        std::cout << e;
    }
    return 0;
}