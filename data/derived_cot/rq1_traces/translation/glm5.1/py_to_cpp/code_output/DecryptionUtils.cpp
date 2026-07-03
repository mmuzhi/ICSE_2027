#include <string>
#include <vector>
#include <cctype>

class DecryptionUtils {
private:
    std::string key;

public:
    DecryptionUtils(std::string key) : key(std::move(key)) {}

    std::string caesar_decipher(const std::string& ciphertext, int shift) {
        std::string plaintext = "";
        for (char c : ciphertext) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                int ascii_offset = std::isupper(static_cast<unsigned char>(c)) ? 65 : 97;
                // C++ modulo can be negative for negative operands, so we add 26 and modulo again to mimic Python's behavior
                char shifted_char = ((c - ascii_offset - shift) % 26 + 26) % 26 + ascii_offset;
                plaintext += shifted_char;
            } else {
                plaintext += c;
            }
        }
        return plaintext;
    }

    std::string vigenere_decipher(const std::string& ciphertext) {
        std::string decrypted_text = "";
        int key_index = 0;
        for (char c : ciphertext) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char key_char = std::tolower(static_cast<unsigned char>(key[key_index % key.length()]));
                int shift = key_char - 'a';
                char lower_c = std::tolower(static_cast<unsigned char>(c));
                char decrypted_char = ((lower_c - 'a' - shift) % 26 + 26) % 26 + 'a';
                decrypted_text += std::isupper(static_cast<unsigned char>(c)) ? std::toupper(static_cast<unsigned char>(decrypted_char)) : decrypted_char;
                key_index++;
            } else {
                decrypted_text += c;
            }
        }
        return decrypted_text;
    }

    std::string rail_fence_decipher(const std::string& encrypted_text, int rails) {
        int n = encrypted_text.length();
        std::vector<std::vector<char>> fence(rails, std::vector<char>(n, '\n'));
        
        int direction = -1;
        int row = 0, col = 0;

        for (int i = 0; i < n; ++i) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            fence[row][col] = '\0'; // Use null character to represent the empty string marker ''
            col += 1;
            row += direction;
        }

        int index = 0;
        for (int i = 0; i < rails; ++i) {
            for (int j = 0; j < n; ++j) {
                if (fence[i][j] == '\0') {
                    fence[i][j] = encrypted_text[index];
                    index += 1;
                }
            }
        }

        std::string plain_text = "";
        direction = -1;
        row = 0;
        col = 0;
        for (int i = 0; i < n; ++i) {
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            plain_text += fence[row][col];
            col += 1;
            row += direction;
        }

        return plain_text;
    }
};