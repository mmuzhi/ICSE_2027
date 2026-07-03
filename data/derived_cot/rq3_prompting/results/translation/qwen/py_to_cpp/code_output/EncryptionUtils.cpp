#include <string>
#include <vector>
#include <cctype>
#include <iostream>

class EncryptionUtils {
public:
    explicit EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (std::isalpha(c)) {
                int offset = std::isupper(c) ? 'A' : 'a';
                char shifted_char = static_cast<char>((static_cast<int>(c) - offset + shift % 26 + 26) % 26 + offset);
                ciphertext += shifted_char;
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
                int shift = std::tolower(key[key[key_index % key.size()]]) - 'a';
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
        if (rails == 0) {
            return plain_text;
        }
        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\0'));
        int direction = -1;
        int row = 0;
        int col = 0;

        for (char c : plain_text) {
            fence[row][col] = c;
            col++;
            if (row == 0 || row == rails - 1) {
                direction *= -1;
            }
            row += direction;
        }

        std::string encrypted_text;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < n; j++) {
                if (fence[i][j] != '\0') {
                    encrypted_text += fence[i][j];
                }
            }
        }
        return encrypted_text;
    }

private:
    std::string key;
};