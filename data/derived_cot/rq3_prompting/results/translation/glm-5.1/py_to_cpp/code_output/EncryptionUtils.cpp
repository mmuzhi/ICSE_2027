#include <string>
#include <vector>
#include <cctype>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_cipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                int ascii_offset = std::isupper(static_cast<unsigned char>(c)) ? 65 : 97;
                char shifted = static_cast<char>(((c - ascii_offset + shift) % 26 + 26) % 26 + ascii_offset);
                ciphertext += shifted;
            } else {
                ciphertext += c;
            }
        }
        return ciphertext;
    }

    std::string vigenere_cipher(const std::string& plain_text) {
        std::string encrypted_text;
        int key_index = 0;
        for (char c : plain_text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                int shift = std::tolower(static_cast<unsigned char>(key[key_index % key.size()])) - 'a';
                char encrypted_char = static_cast<char>((std::tolower(static_cast<unsigned char>(c)) - 'a' + shift) % 26 + 'a');
                encrypted_text += std::isupper(static_cast<unsigned char>(c))
                    ? static_cast<char>(std::toupper(static_cast<unsigned char>(encrypted_char)))
                    : encrypted_char;
                key_index++;
            } else {
                encrypted_text += c;
            }
        }
        return encrypted_text;
    }

    std::string rail_fence_cipher(const std::string& plain_text, int rails) {
        std::vector<std::vector<char>> fence(rails, std::vector<char>(plain_text.size(), '\n'));
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
            for (size_t j = 0; j < plain_text.size(); j++) {
                if (fence[i][j] != '\n') {
                    encrypted_text += fence[i][j];
                }
            }
        }
        return encrypted_text;
    }
};