#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

class BinaryInfo {
private:
    double zeroes;
    double ones;
    int bitLength;

public:
    BinaryInfo(double zeroes, double ones, int bitLength)
        : zeroes(zeroes), ones(ones), bitLength(bitLength) {}

    double getZeroes() const { return zeroes; }
    double getOnes() const { return ones; }
    int getBitLength() const { return bitLength; }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3)
            << "{Zeroes: " << zeroes << ", Ones: " << ones
            << ", Bit length: " << bitLength << "}";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const BinaryInfo& info) {
        os << info.toString();
        return os;
    }
};

class BinaryDataProcessor {
private:
    std::string binaryString;

public:
    BinaryDataProcessor(const std::string& binaryString)
        : binaryString(binaryString) {
        cleanNonBinaryChars();
    }

    void cleanNonBinaryChars() {
        binaryString.erase(
            std::remove_if(binaryString.begin(), binaryString.end(),
                [](char c) { return c != '0' && c != '1'; }),
            binaryString.end());
    }

    BinaryInfo calculateBinaryInfo() {
        int zeroesCount = static_cast<int>(std::count(binaryString.begin(), binaryString.end(), '0'));
        int onesCount = static_cast<int>(std::count(binaryString.begin(), binaryString.end(), '1'));
        int totalLength = static_cast<int>(binaryString.length());

        double zeroesPercentage = static_cast<double>(zeroesCount) / totalLength;
        double onesPercentage = static_cast<double>(onesCount) / totalLength;

        return BinaryInfo(zeroesPercentage, onesPercentage, totalLength);
    }

    std::string convertToAscii() {
        std::string asciiString;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            asciiString += static_cast<char>(decimal);
        }
        return asciiString;
    }

    std::string convertToUtf8() {
        std::string utf8String;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            utf8String += static_cast<char>(decimal);
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
    std::cout << bdp.calculateBinaryInfo() << std::endl;
    std::cout << bdp.convertToAscii() << std::endl;
    std::cout << bdp.convertToUtf8() << std::endl;
    return 0;
}