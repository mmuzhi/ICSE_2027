#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class BinaryInfo {
public:
    double zeroes;
    double ones;
    int bitLength;

    BinaryInfo(double zeroes, double ones, int bitLength)
        : zeroes(zeroes), ones(ones), bitLength(bitLength) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3);
        oss << "{Zeroes: " << zeroes << ", Ones: " << ones << ", Bit length: " << bitLength << "}";
        return oss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const BinaryInfo& info) {
    os << info.toString();
    return os;
}

class BinaryDataProcessor {
private:
    std::string binaryString;

    void cleanNonBinaryChars() {
        binaryString = std::regex_replace(binaryString, std::regex("[^01]"), "");
    }

public:
    BinaryDataProcessor(const std::string& input) : binaryString(input) {
        cleanNonBinaryChars();
    }

    BinaryInfo calculateBinaryInfo() const {
        int zeroesCount = std::count(binaryString.begin(), binaryString.end(), '0');
        int onesCount = std::count(binaryString.begin(), binaryString.end(), '1');
        int totalLength = binaryString.length();

        double zeroesPercentage = static_cast<double>(zeroesCount) / totalLength;
        double onesPercentage = static_cast<double>(onesCount) / totalLength;

        return BinaryInfo(zeroesPercentage, onesPercentage, totalLength);
    }

    std::string convertToAscii() const {
        std::string asciiString;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            if (i + 8 > binaryString.length()) {
                throw std::out_of_range("Binary string length is not a multiple of 8");
            }
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            asciiString += static_cast<char>(decimal);
        }
        return asciiString;
    }

    std::string convertToUtf8() const {
        // Identical to convertToAscii in this implementation
        std::string utf8String;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            if (i + 8 > binaryString.length()) {
                throw std::out_of_range("Binary string length is not a multiple of 8");
            }
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            utf8String += static_cast<char>(decimal);
        }
        return utf8String;
    }

    const std::string& getBinaryString() const {
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