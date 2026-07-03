#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

class DecryptionUtils {
private:
    std::string key;

public:
    DecryptionUtils(std::string key) : key(key) {}

    std::string caesar_decipher(std::string ciphertext, int shift) {
        std::string plaintext;
        for (char c : ciphertext) {
            if (std::isalpha(c)) {
                char base = std::isupper(c) ? 'A' : 'a';
                int shifted = (c - base - shift) % 26;
                if (shifted < 0) {
                    shifted += 26;
                }
                plaintext += static_cast<char>(base + shifted);
            } else {
                plaintext += c;
            }
        }
        return plaintext;
    }

    std::string vigenere_decipher(std::string ciphertext) {
        if (key.empty()) {
            throw std::invalid_argument("Key must not be empty");
        }

        std::string decrypted_text;
        int key_index = 0;
        for (char c : ciphertext) {
            if (std::isalpha(c)) {
                char key_char = std::tolower(key[key_index % key.length()]);
                int shift = key_char - 'a';
                char lower_c = std::tolower(c);
                int shifted = (lower_c - 'a' - shift) % 26;
                if (shifted < 0) {
                    shifted += 26;
                }
                char decrypted_char = 'a' + shifted;
                if (std::isupper(c)) {
                    decrypted_char = std::toupper(decrypted_char);
                }
                decrypted_text += decrypted_char;
                key_index++;
            } else {
                decrypted_text += c;
            }
        }
        return decrypted_text;
    }

    std::string rail_fence_decipher(std::string encrypted_text, int rails) {
        if (rails <= 0) {
            return "";
        }
        int n = encrypted_text.length();
        if (rails == 1 || n == 0) {
            return encrypted_text;
        }

        std::vector<int> lengths(rails, 0);
        int row = 0;
        int dir = -1;
        for (int i = 0; i < n; i++) {
            lengths[row]++;
            if (row == 0 || row == rails - 1) {
                dir = -dir;
            }
            row += dir;
        }

        std::vector<std::string> rails_str;
        int start = 0;
        for (int i = 0; i < rails; i++) {
            rails_str.push_back(encrypted_text.substr(start, lengths[i]));
            start += lengths[i];
        }

        std::vector<int> ptr(rails, 0);
        row = 0;
        dir = -1;
        std::string plain_text;
        for (int i = 0; i < n; i++) {
            plain_text += rails_str[row][ptr[row]];
            ptr[row]++;
            if (row == 0 || row == rails - 1) {
                dir = -dir;
            }
            row += dir;
        }

        return plain_text;
    }
};