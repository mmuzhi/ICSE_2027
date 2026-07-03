#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <stdexcept>

class BinaryInfo {
private:
    double zeroes;
    double ones;
    int bitLength;

public:
    BinaryInfo(double zeroes, double ones, int bitLength) : zeroes(zeroes), ones(ones), bitLength(bitLength) {}

    double getZeroes() const { return zeroes; }
    double getOnes() const { return ones; }
    int getBitLength() const { return bitLength; }

    std::string toString() const {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "{Zeroes: %.3f, Ones: %.3f, Bit length: %d}", zeroes, ones, bitLength);
        return std::string(buffer);
    }
};

class BinaryDataProcessor {
private:
    std::string binaryString;

    void cleanNonBinaryChars() {
        auto it = std::remove_if(binaryString.begin(), binaryString.end(),
            [](char c) { return c != '0' && c != '1'; });
        binaryString.erase(it, binaryString.end());
    }

public:
    BinaryDataProcessor(std::string binaryString) : binaryString(std::move(binaryString)) {
        cleanNonBinaryChars();
    }

    BinaryInfo calculateBinaryInfo() {
        int totalLength = binaryString.length();
        int zeroesCount = std::count(binaryString.begin(), binaryString.end(), '0');
        int onesCount = totalLength - zeroesCount;

        double zeroesPercentage = static_cast<double>(zeroesCount) / totalLength;
        double onesPercentage = static_cast<double>(onesCount) / totalLength;

        return BinaryInfo(zeroesPercentage, onesPercentage, totalLength);
    }

    std::string convertToAscii() {
        std::string asciiString;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            if (i + 8 > binaryString.length()) {
                throw std::out_of_range("Index out of bounds");
            }
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            asciiString.push_back(static_cast<char>(decimal));
        }
        return asciiString;
    }

    std::string convertToUtf8() {
        std::string utf8String;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            if (i + 8 > binaryString.length()) {
                throw std::out_of_range("Index out of bounds");
            }
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            utf8String.push_back(static_cast<char>(decimal));
        }
        return utf8String;
    }

    std::string getBinaryString() const {
        return binaryString;
    }
};

int main() {
    BinaryDataProcessor bdp("0110100001100101011011000110110001101111");
    std::cout << bdp.getBinaryString() << std::endl;
    BinaryInfo info = bdp.calculateBinaryInfo();
    std::cout << info.toString() << std::endl;
    std::cout << bdp.convertToAscii() << std::endl;
    std::cout << bdp.convertToUtf8() << std::endl;
    return 0;
}