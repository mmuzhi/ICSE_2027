#include <string>
#include <vector>
#include <cctype>
#include <cmath>

class DecryptionUtils {
private:
    std::string key;

public:
    DecryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_decipher(const std::string& ciphertext, int shift) {
        std::string plaintext;
        for (char c : ciphertext) {
            if (std::isalpha(c)) {
                int ascii_offset = std::isupper(c) ? 'A' : 'a';
                char shifted_char = static_cast<char>((c - ascii_offset - shift + 26) % 26 + ascii_offset);
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
                int shift = std::toupper(key[key_index % key.length()]) - 'A';
                char shifted_char = static_cast<char>((std::tolower(c) - 'a' - shift + 26) % 26 + 'a');
                decrypted_text += std::isupper(c) ? std::toupper(shifted_char) : shifted_char;
                key_index++;
            } else {
                decrypted_text += c;
            }
        }
        return decrypted_text;
    }

    std::string rail_fence_decipher(const std::string& encrypted_text, int rails) {
        if (rails <= 0 || rails > encrypted_text.length() || encrypted_text.length() == 0) {
            return encrypted_text;
        }

        int n = encrypted_text.length();
        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\0'));
        int row = 0, col = 0;
        int direction = -1;

        for (int i = 0; i < n; i++) {
            fence[row][col] = '\1'; // Mark as visited
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            row += direction;
            col++;
        }

        int index = 0;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < n; j++) {
                if (fence[i][j] == '\1') {
                    fence[i][j] = encrypted_text[index++];
                }
            }
        }

        std::string plain_text;
        row = 0, col = 0, direction = -1;
        for (int i = 0; i < n; i++) {
            plain_text += fence[row][col];
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            row += direction;
            col++;
        }

        return plain_text;
    }
};