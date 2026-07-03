#include <string>
#include <vector>

class EncryptionUtils {
private:
    std::string key;

public:
    EncryptionUtils(const std::string& key) : key(key) {}

    std::string caesarCipher(const std::string& plaintext, int shift) {
        std::string ciphertext;
        for (char c : plaintext) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                char shiftedChar = static_cast<char>((c - base + shift % 26 + 26) % 26 + base);
                ciphertext += shiftedChar;
            } else {
                ciphertext += c;
            }
        }
        return ciphertext;
    }

    std::string vigenereCipher(const std::string& plaintext) {
        std::string encryptedText;
        int keyIndex = 0;
        for (char c : plaintext) {
            if (isalpha(c)) {
                char keyChar = tolower(key[keyIndex % key.length()]);
                int shift = keyChar - 'a';
                char plainChar = tolower(c);
                char encryptedChar = static_cast<char>((plainChar - 'a' + shift % 26 + 26) % 26 + 'a');
                encryptedText += isupper(c) ? toupper(encryptedChar) : encryptedChar;
                keyIndex++;
            } else {
                encryptedText += c;
            }
        }
        return encryptedText;
    }

    std::string railFenceCipher(const std::string& plaintext, int rails) {
        if (rails <= 0 || rails > plaintext.length() || plaintext.empty()) {
            return plaintext;
        }

        std::vector<std::string> railsVec(rails, "");
        int direction = -1;
        int row = 0;

        for (char c : plaintext) {
            railsVec[row] += c;
            if (row == 0 || row == rails - 1) {
                direction *= -1;
            }
            row += direction;
        }

        std::string result;
        for (const auto& rail : railsVec) {
            result += rail;
        }
        return result;
    }
};