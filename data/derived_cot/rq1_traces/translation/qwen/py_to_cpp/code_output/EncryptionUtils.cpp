#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (std::isalpha(c)) {
                if (std::isupper(c)) {
                    ciphertext += static_cast<char>((static_cast<int>(c) - 'A' + shift) % 26 + 'A');
                } else {
                    ciphertext += static_cast<char>((static_cast<int>(c) - 'a' + shift) % 26 + 'a');
                }
            } else {
                ciphertext += c;
            }
        }
        return ciphertext;
    }

    std::string vigenere_cipher(const std::string& plaintext) {
        std::string encrypted_text;
        int key_index = 0;
        for (char c : plaintext) {
            if (std::isalpha(c)) {
                int shift = std::toupper(key[key[key_index % key.length()]]) - 'A';
                char shifted_char;
                if (std::isupper(c)) {
                    shifted_char = static_cast<char>((static_cast<int>(c) - 'A' + shift) % 26 + 'A');
                } else {
                    shifted_char = static_cast<char>((static_cast<int>(c) - 'a' + shift) % 26 + 'a');
                }
                encrypted_text += shifted_char;
                key_index++;
            } else {
                encrypted_text += c;
            }
        }
        return encrypted_text;
    }

    std::string rail_fence_cipher(const std::string& plain_text, int rails) {
        int n = plain_text.length();
        if (rails == 0 || n == 0) {
            return plain_text;
        }

        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\n'));
        int row = 0;
        int col = 0;
        int direction = -1;

        for (char c : plain_text) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence[row][col] = c;
            col++;
            row += direction;
        }

        std::string encrypted_text;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < n; j++) {
                if (fence[i][j] != '\n') {
                    encrypted_text += fence[i][j];
                }
            }
        }
        return encrypted_text;
    }
};