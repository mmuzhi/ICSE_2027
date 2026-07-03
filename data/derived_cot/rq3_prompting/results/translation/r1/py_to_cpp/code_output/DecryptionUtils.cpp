#include <string>
#include <vector>
#include <cctype>

class DecryptionUtils {
private:
    std::string key;

public:
    DecryptionUtils(const std::string& key) : key(key) {}

    std::string caesar_decipher(const std::string& ciphertext, int shift) {
        std::string plaintext;
        for (char ch : ciphertext) {
            if (std::isalpha(ch)) {
                int ascii_offset = std::isupper(ch) ? 65 : 97;
                int original = static_cast<int>(ch) - ascii_offset;
                int decoded = ((original - shift) % 26 + 26) % 26; // handle negative shifts
                plaintext.push_back(static_cast<char>(decoded + ascii_offset));
            } else {
                plaintext.push_back(ch);
            }
        }
        return plaintext;
    }

    std::string vigenere_decipher(const std::string& ciphertext) {
        std::string decrypted_text;
        int key_index = 0;
        int key_len = key.length();
        for (char ch : ciphertext) {
            if (std::isalpha(ch)) {
                int shift = std::tolower(key[key_index % key_len]) - 'a';
                char lower_ch = std::tolower(ch);
                int decoded = ( (lower_ch - 'a' - shift) % 26 + 26 ) % 26;
                char decrypted_char = static_cast<char>(decoded + 'a');
                if (std::isupper(ch)) {
                    decrypted_char = std::toupper(decrypted_char);
                }
                decrypted_text.push_back(decrypted_char);
                key_index++;
            } else {
                decrypted_text.push_back(ch);
            }
        }
        return decrypted_text;
    }

    std::string rail_fence_decipher(const std::string& encrypted_text, int rails) {
        int len = encrypted_text.length();
        if (rails <= 1) {
            return encrypted_text; // no zigzag needed
        }
        std::vector<std::vector<char>> fence(rails, std::vector<char>(len, ' '));
        std::vector<std::vector<bool>> occupied(rails, std::vector<bool>(len, false));

        // Mark the zigzag pattern
        int row = 0;
        int col = 0;
        int direction = -1; // will be flipped to +1 at start
        for (int i = 0; i < len; ++i) {
            occupied[row][col] = true;
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            row += direction;
            col += 1;
        }

        // Fill the occupied positions from encrypted_text
        int index = 0;
        for (int i = 0; i < rails; ++i) {
            for (int j = 0; j < len; ++j) {
                if (occupied[i][j]) {
                    fence[i][j] = encrypted_text[index];
                    index++;
                }
            }
        }

        // Read in zigzag order to reconstruct plaintext
        std::string plain_text;
        row = 0;
        col = 0;
        direction = -1;
        for (int i = 0; i < len; ++i) {
            plain_text.push_back(fence[row][col]);
            if (row == 0 || row == rails - 1) {
                direction = -direction;
            }
            row += direction;
            col += 1;
        }
        return plain_text;
    }
};