#include "Main.h"

int main() {
    try {
        std::cout << "Set 1 Challenge 1" << std::endl;
        std::cout << cpt::hex2base64(std::string("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")) << std::endl;

    } catch (std::string e) {
        std::cout << e << std::endl;
    }

    try {
        std::cout << "Set 1 Challenge 2" << std::endl;
        std::cout << cpt::hexXor(std::string("1c0111001f010100061a024b53535009181c"), std::string("686974207468652062756c6c277320657965")) << std::endl;

    } catch (std::string e) {
        std::cout << e << std::endl;
    }

    try {
        std::cout << "Set 1 Challenge 3" << std::endl;
        std::string encodedMessage = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
        std::string hexMessage = cpt::decodeSingleByteCipher(encodedMessage);
        std::string binaryMessage = cpt::hex2binary(hexMessage);
        for (unsigned i = 0; i < binaryMessage.size(); i += 8) {
            std::cout << static_cast<char>(cpt::binary2decimal(binaryMessage.substr(i, 8)));
        }

    } catch (std::string e) {
        std::cout << e;
    }

    try {
        std::cout << std::endl << "Set 1 Challenge 4" << std::endl;
        std::ifstream file("4.txt", std::ifstream::in);

        std::deque<std::string> hexBlocks;
        std::deque<std::string> decodedHexBlocks;
        std::deque<unsigned short> scores;
        unsigned index = 0;
        while (file.good()) {
            if (index + 1 > decodedHexBlocks.size()) {
                hexBlocks.resize(index + 1);
                decodedHexBlocks.resize(index + 1);
                scores.resize(index + 1);
            }

            std::getline(file, hexBlocks[index]);
            ++index;
        }

        std::thread threads[NUM_THREADS];
        std::mutex dataAccess;
        for (unsigned lineIndex = 0; lineIndex < hexBlocks.size(); ++lineIndex) {
            if (threads[lineIndex % NUM_THREADS].joinable()) {
                threads[lineIndex % NUM_THREADS].join();
            }
            threads[lineIndex % NUM_THREADS] = std::thread([&, lineIndex](){
                std::string decoded = cpt::decodeSingleByteCipher(hexBlocks[lineIndex]);
                unsigned short score = cpt::getPlainTextScore(decoded);

                std::lock_guard<std::mutex> lock(dataAccess);
                decodedHexBlocks[lineIndex] = decoded;
                scores[lineIndex] = score;
            });
        }

        for (unsigned i = 0; i < NUM_THREADS; ++i) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }

        unsigned highestScore = 0;
        unsigned highestScoreIndex = 0;
        for (unsigned i = 0; i < scores.size(); ++i) {
            if (scores[i] > highestScore) {
                highestScore = scores[i];
                highestScoreIndex = i;
            }
        }

        std::cout << "Line number for encoded hexadecimal is most likely: " << highestScoreIndex + 1 << std::endl;
        std::string hexMessage = decodedHexBlocks[highestScoreIndex];
        std::string binaryMessage = cpt::hex2binary(hexMessage);
        for (unsigned i = 0; i < binaryMessage.size(); i += 8) {
            std::cout << static_cast<char>(cpt::binary2decimal(binaryMessage.substr(i, 8)));
        }
    } catch (std::string e) {
        std::cout << e << std::endl;
    }
    try {
        std::cout << "Set 1 Challenge 5" << std::endl;
        std::string message = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
        std::string key = "ICE";
        std::cout << cpt::repeatingKeyXor(message, key);
    } catch (std::string e) {
        std::cout << e << std::endl;
    }

    return 0;
}