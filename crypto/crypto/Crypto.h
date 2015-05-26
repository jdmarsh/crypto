#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

namespace cpt {
    std::string hexXor(std::string, std::string);

    std::string hex2base64(std::string);
    std::string hex2binary(std::string);
    std::string binary2hex(std::string);
    std::string binary2base64(std::string);
}

#endif