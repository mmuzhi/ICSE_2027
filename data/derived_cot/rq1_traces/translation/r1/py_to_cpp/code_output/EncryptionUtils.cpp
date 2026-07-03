#include <string>
#include <vector>
#include <cctype>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(std::string key) : key(key) {}

    std::string caesar_cipher(std::string plaintext, int shift) {
        std::string ciphertext = "";
        for (char c : plaintext) {
            if (std::isalpha(c)) {
                char ascii_offset = std::isupper(c) ? 'A' : 'a';
                char shifted_char = (c - ascii_offset + shift) % 26;
                if (shifted_char < 0) {
                    shifted_char += 26;
                }
                ciphertext += (shifted_char + ascii_offset);
            } else {
                ciphertext += c;
            }
        }
        return ciphertext;
    }

    std::string vigenere_cipher(std::string plain_text) {
        std::string encrypted_text = "";
        int key_index = 0;
        for (char c : plain_text) {
            if (std::isalpha(c)) {
                char key_char = std::tolower(this->key[key_index % this->key.length()]);
                int shift = key_char - 'a';
                char base = std::isupper(c) ? 'A' : 'a';
                char encrypted_char = (std::tolower(c) - 'a' + shift) % 26 + 'a';
                if (std::isupper(c)) {
                    encrypted_text += std::toupper(encrypted_char);
                } else {
                    encrypted_text += encrypted_char;
                }
                key_index++;
            } else {
                encrypted_text += c;
            }
        }
        return encrypted_text;
    }

    std::string rail_fence_cipher(std::string plain_text, int rails) {
        if (rails <= 1) {
            return plain_text;
        }
        std::vector<std::vector<char>> fence(rails, std::vector<char>(plain_text.length(), '\n'));
        int direction = -1;
        int row = 0, col = 0;

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
            for (int j = 0; j < plain_text.length(); j++) {
                if (fence[i][j] != '\n') {
                    encrypted_text += fence[i][j];
                }
            }
        }
        return encrypted_text;
    }
};