#include <string>
#include <vector>
#include <cctype>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char asciiOffset = std::isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';
                char shiftedChar = (c - asciiOffset + shift) % 26 + asciiOffset;
                ciphertext += shiftedChar;
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
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char keyChar = key[keyIndex % key.length()];
                int shift = std::tolower(static_cast<unsigned char>(keyChar)) - 'a';
                char lowerC = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                char encryptedLower = (lowerC - 'a' + shift) % 26 + 'a';
                if (std::isupper(static_cast<unsigned char>(c))) {
                    encryptedText += std::toupper(static_cast<unsigned char>(encryptedLower));
                } else {
                    encryptedText += encryptedLower;
                }
                keyIndex++;
            } else {
                encryptedText += c;
            }
        }
        return encryptedText;
    }

    std::string rail_fence_cipher(const std::string& plainText, int rails) {
        int n = plainText.length();
        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\n'));
        int direction = -1;
        int row = 0, col = 0;

        for (char c : plainText) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence[row][col] = c;
            col++;
            row += direction;
        }

        std::string encryptedText;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < n; j++) {
                if (fence[i][j] != '\n') {
                    encryptedText += fence[i][j];
                }
            }
        }
        return encryptedText;
    }
};