#include "Main.h"

int main() {
    try {
        std::cout << "Set 1 Challenge 1" << std::endl;
        std::cout << cpt::hex2base64(std::string("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")) << std::endl;
        std::cout << "Set 1 Challenge 2" << std::endl;
        std::cout << cpt::hexXor(std::string("1c0111001f010100061a024b53535009181c"),std::string("686974207468652062756c6c277320657965"));
    } catch (std::string e) {
        std::cout << e;
    }
    return 0;
}