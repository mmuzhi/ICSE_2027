class DecryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_decipher(self, ciphertext, shift):
        shift = shift % 26
        plaintext = []
        for c in ciphertext:
            if c.isalpha():
                base = 'A' if c.isupper() else 'a'
                shifted_char = chr((ord(c) - ord(base) - shift + 26) % 26 + ord(base))
                plaintext.append(shifted_char)
            else:
                plaintext.append(c)
        return ''.join(plaintext)

    def vigenere_decipher(self, ciphertext):
        decrypted_text = []
        key_length = len(self.key)
        key_index = 0
        for c in ciphertext:
            if c.isalpha():
                shift = ord(self.key[key_index % key_length].lower()) - ord('a')
                base = 'a' if c.islower() else 'A'
                decrypted_char = chr((ord(c.lower()) - ord('a') - shift + 26) % 26 + ord('a'))
                if c.isupper():
                    decrypted_char = decrypted_char.upper()
                decrypted_text.append(decrypted_char)
                key_index += 1
            else:
                decrypted_text.append(c)
        return ''.join(decrypted_text)

    def rail_fence_decipher(self, encrypted_text, rails):
        n = len(encrypted_text)
        if rails <= 1:
            return encrypted_text

        fence = [['\0'] * n for _ in range(rails)]
        
        row, col = 0, 0
        direction = -1
        for i in range(n):
            fence[row][col] = '*'
            if row == 0 or row == rails - 1:
                direction = -direction
            row += direction
            col += 1

        index = 0
        for r in range(rails):
            for c in range(n):
                if fence[r][c] == '*':
                    fence[r][c] = encrypted_text[index]
                    index += 1

        row, col, direction = 0, 0, -1
        plain_text = []
        for i in range(n):
            plain_text.append(fence[row][col])
            if row == 0 or row == rails - 1:
                direction = -direction
            row += direction
            col += 1

        return ''.join(plain_text)