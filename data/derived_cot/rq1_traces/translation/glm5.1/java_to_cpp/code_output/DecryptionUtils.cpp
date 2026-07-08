#include <string>
#include <vector>
#include <cctype>

namespace org::example {

class DecryptionUtils {
private:
    std::string key;

public:
    DecryptionUtils(std::string key) : key(std::move(key)) {}

    std::string caesarDecipher(const std::string& ciphertext, int shift) {
        std::string plaintext;
        plaintext.reserve(ciphertext.length());
        shift = shift % 26;
        for (char ch : ciphertext) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                int asciiOffset = std::isupper(static_cast<unsigned char>(ch)) ? 'A' : 'a';
                char shiftedChar = static_cast<char>(((ch - asciiOffset - shift + 26) % 26) + asciiOffset);
                plaintext += shiftedChar;
            } else {
                plaintext += ch;
            }
        }
        return plaintext;
    }

    std::string vigenereDecipher(const std::string& ciphertext) {
        std::string decryptedText;
        decryptedText.reserve(ciphertext.length());
        int keyIndex = 0;
        for (char ch : ciphertext) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                int shift = std::tolower(static_cast<unsigned char>(key[keyIndex % static_cast<int>(key.length())])) - 'a';
                char base = std::isupper(static_cast<unsigned char>(ch)) ? 'A' : 'a';
                char decryptedChar = static_cast<char>(((ch - base - shift + 26) % 26) + base);
                decryptedText += decryptedChar;
                keyIndex++;
            } else {
                decryptedText += ch;
            }
        }
        return decryptedText;
    }

    std::string railFenceDecipher(const std::string& encryptedText, int rails) {
        std::vector<std::vector<char>> fence(rails, std::vector<char>(encryptedText.length(), '\0'));

        int direction = -1;
        int row = 0, col = 0;

        for (size_t i = 0; i < encryptedText.length(); i++) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence[row][col++] = '*';
            row += direction;
        }

        int index = 0;
        for (int i = 0; i < rails; i++) {
            for (size_t j = 0; j < encryptedText.length(); j++) {
                if (fence[i][j] == '*') {
                    fence[i][j] = encryptedText[index++];
                }
            }
        }

        std::string plainText;
        plainText.reserve(encryptedText.length());
        direction = -1;
        row = 0;
        col = 0;

        for (size_t i = 0; i < encryptedText.length(); i++) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            plainText += fence[row][col++];
            row += direction;
        }

        return plainText;
    }
};

} // namespace org::example