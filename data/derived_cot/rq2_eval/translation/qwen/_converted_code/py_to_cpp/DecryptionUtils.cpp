#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

class DecryptionUtils {
public:
    explicit DecryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_decipher(const std::string& ciphertext, int shift) {
        std::string plaintext;
        for (char c : ciphertext) {
            if (std::isalpha(c)) {
                int ascii_offset = std::isupper(c) ? 'A' : 'a';
                char shifted_char = static_cast<char>((static_cast<int>(c) - ascii_offset - shift % 26 + 26) % 26 + ascii_offset);
                plaintext += shifted_char;
            } else {
                plaintext += c;
            }
        }
        return plaintext;
    }

    std::string vigenere_decipher(const std::string& ciphertext) {
        std::string decrypted_text;
        int key_index = 0;
        for (char c : ciphertext) {
            if (std::isalpha(c)) {
                char key_char = std::tolower(key[key_index % key.length()]);
                int shift = key_char - 'a';
                char shifted_char = static_cast<char>((static_cast<int>(c) - 'a' - shift + 26) % 26 + 'a');
                if (std::isupper(c)) {
                    shifted_char = std::toupper(shifted_char);
                }
                decrypted_text += shifted_char;
                key_index++;
            } else {
                decrypted_text += c;
            }
        }
        return decrypted_text;
    }

    std::string rail_fence_decipher(const std::string& encrypted_text, int rails) {
        int len = encrypted_text.length();
        std::vector<std::vector<char>> fence(rails, std::vector<char>(len, '\0'));
        int direction = -1;
        int row = 0, col = 0;

        for (int i = 0; i < len; ++i) {
            fence[row][col] = '\0';
            if (row == 0 || row == rails - 1) {
                direction *= -1;
            }
            row += direction;
            col++;
        }

        int index = 0;
        for (int i = 0; i < rails; ++i) {
            for (int j = 0; j < len; ++j) {
                if (fence[i][j] == '\0') {
                    fence[i][j] = encrypted_text[index];
                    index++;
                }
            }
        }

        direction = -1;
        row = 0;
        col = 0;
        std::string plaintext;
        for (int i = 0; i < len; ++i) {
            if (row == 0 || row == rails - 1) {
                direction *= -1;
            }
            plaintext += fence[row][col];
            col++;
            row += direction;
        }

        return plaintext;
    }

private:
    std::string key;
};