#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <iomanip>

struct BinaryInfo {
    double zeroes;
    double ones;
    int bitLength;

    BinaryInfo(double zeroes, double ones, int bitLength) : zeroes(zeroes), ones(ones), bitLength(bitLength) {}

    std::string toString() {
        std::ostringstream oss;
        oss << "{Zeroes: " << std::fixed << std::setprecision(3) << zeroes << ", Ones: " << std::fixed << std::setprecision(3) << ones << ", Bit length: " << bitLength << "}";
        return oss.str();
    }
};

class BinaryDataProcessor {
private:
    std::string binaryString;

public:
    BinaryDataProcessor(const std::string& binaryString) {
        this->binaryString = binaryString;
        cleanNonBinaryChars();
    }

    void cleanNonBinaryChars() {
        std::regex re("[^01]");
        this->binaryString = std::regex_replace(this->binaryString, re, "");
    }

    BinaryInfo calculateBinaryInfo() {
        int totalLength = this->binaryString.length();
        int zeroesCount = std::count(this->binaryString.begin(), this->binaryString.end(), '0');
        int onesCount = totalLength - zeroesCount;

        double zeroesPercentage = static_cast<double>(zeroesCount) / totalLength;
        double onesPercentage = static_cast<double>(onesCount) / totalLength;

        return BinaryInfo(zeroesPercentage, onesPercentage, totalLength);
    }

    std::string convertToAscii() {
        std::string result;
        for (int i = 0; i < this->binaryString.length(); i += 8) {
            std::string byteString = this->binaryString.substr(i, 8);
            try {
                int decimal = std::stoi(byteString, nullptr, 2);
                result += static_cast<char>(decimal);
            } catch (...) {
                throw;
            }
        }
        return result;
    }

    std::string convertToUtf8() {
        std::string result;
        for (int i = 0; i < this->binaryString.length(); i += 8) {
            std::string byteString = this->binaryString.substr(i, 8);
            try {
                int decimal = std::stoi(byteString, nullptr, 2);
                result += static_cast<char>(decimal);
            } catch (...) {
                throw;
            }
        }
        return result;
    }

    std::string getBinaryString() {
        return this->binaryString;
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