#include <string>
#include <vector>
#include <cctype>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesarCipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (std::isalpha(c)) {
                int asciiOffset = std::isupper(c) ? 'A' : 'a';
                char shiftedChar = static_cast<char>((c - asciiOffset + shift) % 26 + asciiOffset);
                ciphertext.push_back(shiftedChar);
            } else {
                ciphertext.push_back(c);
            }
        }
        return ciphertext;
    }

    std::string vigenereCipher(const std::string& plainText) {
        std::string encryptedText;
        int keyIndex = 0;
        for (char c : plainText) {
            if (std::isalpha(c)) {
                int shift = std::tolower(key[keyIndex % key.length()]) - 'a';
                char encryptedChar = static_cast<char>((std::tolower(c) - 'a' + shift) % 26 + 'a');
                if (std::isupper(c)) {
                    encryptedChar = std::toupper(encryptedChar);
                }
                encryptedText.push_back(encryptedChar);
                keyIndex++;
            } else {
                encryptedText.push_back(c);
            }
        }
        return encryptedText;
    }

    std::string railFenceCipher(const std::string& plainText, int rails) {
        if (rails <= 0) {
            return "";  // Behaves like Java when rails <= 0 would throw, but we keep it safe.
        }
        std::vector<std::vector<char>> fence(rails, std::vector<char>(plainText.length(), '\n'));

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
            for (int j = 0; j < plainText.length(); j++) {
                if (fence[i][j] != '\n') {
                    encryptedText.push_back(fence[i][j]);
                }
            }
        }
        return encryptedText;
    }
};