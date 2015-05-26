#include "Main.h"

int main() {
    try {
        std::cout << cpt::hex2base64(std::string("49"));
    } catch (std::string e) {
        std::cout << e;
    }
    return 0;
}