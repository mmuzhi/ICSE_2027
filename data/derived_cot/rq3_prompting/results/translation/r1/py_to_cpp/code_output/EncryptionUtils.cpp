#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char ch : plaintext) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char base = std::isupper(static_cast<unsigned char>(ch)) ? 'A' : 'a';
                ciphertext += static_cast<char>((ch - base + shift) % 26 + base);
            } else {
                ciphertext += ch;
            }
        }
        return ciphertext;
    }

    std::string vigenere_cipher(const std::string& plain_text) {
        std::string encrypted_text;
        size_t key_index = 0;
        for (char ch : plain_text) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char key_char = std::tolower(static_cast<unsigned char>(key[key_index % key.length()]));
                int shift = key_char - 'a';
                char encrypted_char = static_cast<char>((std::tolower(static_cast<unsigned char>(ch)) - 'a' + shift) % 26 + 'a');
                if (std::isupper(static_cast<unsigned char>(ch))) {
                    encrypted_text += std::toupper(static_cast<unsigned char>(encrypted_char));
                } else {
                    encrypted_text += encrypted_char;
                }
                ++key_index;
            } else {
                encrypted_text += ch;
            }
        }
        return encrypted_text;
    }

    std::string rail_fence_cipher(const std::string& plain_text, int rails) {
        std::vector<std::vector<char>> fence(rails, std::vector<char>(plain_text.size(), '\n'));
        int direction = -1;
        int row = 0;
        size_t col = 0;

        for (char ch : plain_text) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence.at(row).at(col) = ch;
            ++col;
            row += direction;
        }

        std::string encrypted_text;
        for (int i = 0; i < rails; ++i) {
            for (size_t j = 0; j < plain_text.size(); ++j) {
                if (fence[i][j] != '\n') {
                    encrypted_text += fence[i][j];
                }
            }
        }
        return encrypted_text;
    }
};