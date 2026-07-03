#include <iostream>
#include <string>
#include <regex>

struct BinaryInfo {
    double zeroes;
    double ones;
    int bitLength;

    BinaryInfo(double zeroes, double ones, int bitLength) : zeroes(zeroes), ones(ones), bitLength(bitLength) {}
};

class BinaryDataProcessor {
private:
    std::string binaryString;

    void cleanNonBinaryChars() {
        static const std::regex pattern("[^01]");
        this->binaryString = std::regex_replace(this->binaryString, pattern, "");
    }

    BinaryInfo calculateBinaryInfo() {
        int totalLength = this->binaryString.length();
        int zeroesCount = totalLength - this->binaryString.replace("0", "").length();
        int onesCount = totalLength - this->binaryString.replace("1", "").length();
        return BinaryInfo(zeroesCount, onesCount, totalLength);
    }

    std::string convertToText() {
        std::string result;
        for (size_t i = 0; i < this->binaryString.length(); i += 8) {
            std::string byteString = this->binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            result += static_cast<char>(decimal);
        }
        return result;
    }

public:
    BinaryDataProcessor(std::string binaryString) {
        this->binaryString = binaryString;
        cleanNonBinaryChars();
    }

    std::string convertToAscii() {
        return convertToText();
    }

    std::string convertToUtf8() {
        return convertToText();
    }

    std::string getBinaryString() {
        return this->binaryString;
    }
};

int main() {
    BinaryDataProcessor bdp("0110100001100101011011000110110001101111");
    std::cout << bdp.getBinaryString() << std::endl;
    auto info = bdp.calculateBinaryInfo();
    std::cout << info.zeroes << ", " << info.ones << ", " << info.bitLength << std::endl;
    std::cout << bdp.convertToAscii() << std::endl;
    std::cout << bdp.convertToUtf8() << std::endl;
    return 0;
}