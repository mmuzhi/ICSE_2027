#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <iostream>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (std::isalpha(c)) {
                int asciiOffset = std::isupper(c) ? 'A' : 'a';
                int shiftedChar = ((c - asciiOffset + shift) % 26);
                if (shiftedChar < 0) {
                    shiftedChar += 26;
                }
                shiftedChar += asciiOffset;
                ciphertext += static_cast<char>(shiftedChar);
            } else {
                ciphertext += c;
            }
        }
        return ciphertext;
    }

    std::string vigenere_cipher(const std::string& plainText) {
        std::string encryptedText;
        int keyIndex = 0;
        for (char c : plainText) {
            if (std::isalpha(c)) {
                char keyChar = key[keyIndex % key.length()];
                int shift = std::tolower(keyChar) - 'a';
                char originalChar = std::tolower(c);
                char encryptedChar = 'a' + ((originalChar - 'a' + shift) % 26);
                if (std::isupper(c)) {
                    encryptedChar = std::toupper(encryptedChar);
                }
                encryptedText += encryptedChar;
                keyIndex++;
            } else {
                encryptedText += c;
            }
        }
        return encryptedText;
    }

    std::string rail_fence_cipher(const std::string& plainText, int rails) {
        if (rails <= 0) {
            throw std::invalid_argument("Rails must be positive.");
        }
        if (plainText.empty()) {
            return plainText;
        }

        std::vector<std::vector<char>> fence(rails, std::vector<char>(plainText.length(), '\0'));
        int direction = -1;
        int currentRow = 0, currentCol = 0;

        for (char c : plainText) {
            fence[currentRow][currentCol] = c;
            currentCol++;

            if (currentRow == 0 || currentRow == rails - 1) {
                direction *= -1;
            }
            currentRow += direction;
        }

        std::string encryptedText;
        for (int i = 0; i < rails; ++i) {
            for (int j = 0; j < plainText.length(); ++j) {
                if (fence[i][j] != '\0') {
                    encryptedText += fence[i][j];
                }
            }
        }
        return encryptedText;
    }
};