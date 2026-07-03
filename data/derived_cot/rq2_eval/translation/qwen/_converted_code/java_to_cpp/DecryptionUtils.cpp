#include <string>
#include <vector>
#include <cctype>

class DecryptionUtils {
private:
    std::string key;

public:
    explicit DecryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_decipher(const std::string& ciphertext, int shift) {
        std::string plaintext;
        shift %= 26;
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

    std::string vigenere_decipher(const std::string& ciphertext) {
        std::string decryptedText;
        size_t keyIndex = 0;
        for (char ch : ciphertext) {
            if (std::isalpha(ch)) {
                char keyChar = std::tolower(key[keyIndex % key.length()]);
                int shift = keyChar - 'a';
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

    std::string rail_fence_decipher(const std::string& encryptedText, int rails) {
        if (rails <= 0 || encryptedText.empty()) {
            return encryptedText;
        }

        int n = encryptedText.length();
        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\0'));
        int direction = -1;
        int row = 0;
        int col = 0;

        for (int i = 0; i < n; ++i) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence[row][col] = '*';
            col++;
            row += direction;
        }

        int index = 0;
        for (int i = 0; i < rails; ++i) {
            for (int j = 0; j < n; ++j) {
                if (fence[i][j] == '*') {
                    fence[i][j] = encryptedText[index++];
                }
            }
        }

        index = 0;
        direction = -1;
        row = 0;
        col = 0;
        std::string plainText;

        for (int i = 0; i < n; ++i) {
            plainText += fence[row][col++];
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            row += direction;
        }

        return plainText;
    }
};