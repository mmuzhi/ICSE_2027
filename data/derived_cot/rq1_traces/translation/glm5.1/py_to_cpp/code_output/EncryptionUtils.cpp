#include <string>
#include <vector>
#include <cctype>

class EncryptionUtils {
public:
    std::string key;

    EncryptionUtils(std::string key) : key(std::move(key)) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        ciphertext.reserve(plaintext.size());
        for (char ch : plaintext) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                int ascii_offset = std::isupper(static_cast<unsigned char>(ch)) ? 65 : 97;
                // Python's % always returns non-negative; C++ may return negative
                char shifted_char = static_cast<char>(((ch - ascii_offset + shift) % 26 + 26) % 26 + ascii_offset);
                ciphertext += shifted_char;
            } else {
                ciphertext += ch;
            }
        }
        return ciphertext;
    }

    std::string vigenere_cipher(const std::string& plain_text) {
        std::string encrypted_text;
        encrypted_text.reserve(plain_text.size());
        int key_index = 0;
        int key_len = static_cast<int>(key.size());
        for (char ch : plain_text) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                int shift = std::tolower(static_cast<unsigned char>(key[key_index % key_len])) - 'a';
                char encrypted_char = static_cast<char>((std::tolower(static_cast<unsigned char>(ch)) - 'a' + shift) % 26 + 'a');
                if (std::isupper(static_cast<unsigned char>(ch))) {
                    encrypted_char = static_cast<char>(std::toupper(static_cast<unsigned char>(encrypted_char)));
                }
                encrypted_text += encrypted_char;
                key_index++;
            } else {
                encrypted_text += ch;
            }
        }
        return encrypted_text;
    }

    std::string rail_fence_cipher(const std::string& plain_text, int rails) {
        int n = static_cast<int>(plain_text.size());
        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\n'));
        int direction = -1;
        int row = 0, col = 0;

        for (int i = 0; i < n; i++) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence[row][col] = plain_text[i];
            col++;
            row += direction;
        }

        std::string encrypted_text;
        encrypted_text.reserve(n);
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