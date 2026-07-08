#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>

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

public:
    BinaryDataProcessor(const std::string& binaryString) : binaryString(binaryString) {
        cleanNonBinaryChars();
    }

    void cleanNonBinaryChars() {
        std::string result;
        result.reserve(binaryString.size());
        for (char c : binaryString) {
            if (c == '0' || c == '1') {
                result += c;
            }
        }
        binaryString = result;
    }

    BinaryInfo calculateBinaryInfo() const {
        int zeroesCount = 0;
        int onesCount = 0;
        for (char c : binaryString) {
            if (c == '0') zeroesCount++;
            else if (c == '1') onesCount++;
        }
        int totalLength = static_cast<int>(binaryString.length());

        double zeroesPercentage = static_cast<double>(zeroesCount) / totalLength;
        double onesPercentage = static_cast<double>(onesCount) / totalLength;

        return BinaryInfo(zeroesPercentage, onesPercentage, totalLength);
    }

    std::string convertToAscii() const {
        std::string result;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            if (i + 8 > binaryString.length()) {
                throw std::out_of_range("substring end index exceeds string length");
            }
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            result += static_cast<char>(decimal);
        }
        return result;
    }

    std::string convertToUtf8() const {
        std::string result;
        for (size_t i = 0; i < binaryString.length(); i += 8) {
            if (i + 8 > binaryString.length()) {
                throw std::out_of_range("substring end index exceeds string length");
            }
            std::string byteString = binaryString.substr(i, 8);
            int decimal = std::stoi(byteString, nullptr, 2);
            result += static_cast<char>(decimal);
        }
        return result;
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