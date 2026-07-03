#include <string>
#include <cctype>
#include <vector>
#include <cstring>

class DecryptionUtils {
private:
    std::string key;

public:
    DecryptionUtils(const std::string& key) : key(key) {}

    std::string caesarDecipher(const std::string& ciphertext, int shift) {
        std::string plaintext;
        shift = shift % 26;
        for (char ch : ciphertext) {
            if (std::isalpha(ch)) {
                int asciiOffset = std::isupper(ch) ? 'A' : 'a';
                char shiftedChar = static_cast<char>((ch - asciiOffset - shift + 26) % 26 + asciiOffset);
                plaintext += shiftedChar;
            } else {
                plaintext += ch;
            }
        }
        return plaintext;
    }

    std::string vigenereDecipher(const std::string& ciphertext) {
        std::string decryptedText;
        int keyIndex = 0;
        for (char ch : ciphertext) {
            if (std::isalpha(ch)) {
                int shift = std::tolower(key[keyIndex % key.length()]) - 'a';
                char base = std::isupper(ch) ? 'A' : 'a';
                char decryptedChar = static_cast<char>((ch - base - shift + 26) % 26 + base);
                decryptedText += decryptedChar;
                keyIndex++;
            } else {
                decryptedText += ch;
            }
        }
        return decryptedText;
    }

    std::string railFenceDecipher(const std::string& encryptedText, int rails) {
        int len = encryptedText.length();
        std::vector<std::vector<char>> fence(rails, std::vector<char>(len, '\0'));

        int direction = -1;
        int row = 0, col = 0;

        for (int i = 0; i < len; ++i) {
            if (row == 0 || row == rails - 1) {
                direction *= -1;
            }
            fence[row][col++] = '*';
            row += direction;
        }

        int index = 0;
        for (int i = 0; i < rails; ++i) {
            for (int j = 0; j < len; ++j) {
                if (fence[i][j] == '*') {
                    fence[i][j] = encryptedText[index++];
                }
            }
        }

        std::string plainText;
        direction = -1;
        row = 0;
        col = 0;

        for (int i = 0; i < len; ++i) {
            if (row == 0 || row == rails - 1) {
                direction *= -1;
            }
            plainText += fence[row][col++];
            row += direction;
        }

        return plainText;
    }
};