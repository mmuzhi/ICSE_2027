class DecryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_decipher(self, ciphertext, shift):
        plaintext = []
        shift = shift % 26
        for char in ciphertext:
            if char.isupper():
                base = 'A'
                shifted_char = chr(((ord(char) - ord(base) - shift) % 26) + ord(base))
                plaintext.append(shifted_char)
            elif char.islower():
                base = 'a'
                shifted_char = chr(((ord(char) - ord(base) - shift) % 26) + ord(base))
                plaintext.append(shifted_char)
            else:
                plaintext.append(char)
        return ''.join(plaintext)

    def vigenere_decipher(self, ciphertext):
        decrypted_text = []
        key_index = 0
        for char in ciphertext:
            if char.isupper():
                base = 'A'
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                decrypted_char = chr(((ord(char) - ord(base) - shift) % 26) + ord(base))
                decrypted_text.append(decrypted_char)
                key_index += 1
            elif char.islower():
                base = 'a'
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                decrypted_char = chr(((ord(char) - ord(base) - shift) % 26) + ord(base))
                decrypted_text.append(decrypted_char)
                key_index += 1
            else:
                decrypted_text.append(char)
        return ''.join(decrypted_text)

    def rail_fence_decipher(self, encrypted_text, rails):
        if rails <= 0:
            raise ValueError("Number of rails must be at least 1")
        if len(encrypted_text) == 0:
            return encrypted_text
        
        fence = [['' for _ in range(len(encrypted_text))] for _ in range(rails)]
        current_row, current_col = 0, 0
        direction = 1  # 1 for down, -1 for up

        for i in range(len(encrypted_text)):
            fence[current_row][current_col] = '*'
            if current_row == 0 or current_row == rails - 1:
                direction *= -1
            current_row += direction
            current_col += 1

        index = 0
        for i in range(rails):
            for j in range(len(encrypted_text)):
                if fence[i][j] == '*':
                    fence[i][j] = encrypted_text[index]
                    index += 1

        direction = 1
        current_row, current_col = 0, 0
        plaintext = []
        for i in range(len(encrypted_text)):
            plaintext.append(fence[current_row][current_col])
            if current_row == 0 or current_row == rails - 1:
                direction *= -1
            current_row += direction
            current_col += 1

        return ''.join(plaintext)