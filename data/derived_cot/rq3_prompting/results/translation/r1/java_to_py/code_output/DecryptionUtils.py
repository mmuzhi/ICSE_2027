import math

class DecryptionUtils:
    def __init__(self, key: str):
        self.key = key

    def caesarDecipher(self, ciphertext: str, shift: int) -> str:
        plaintext = []
        shift = int(math.fmod(shift, 26))  # match Java's sign-sensitive modulo
        base_a = ord('A')
        base_a_lower = ord('a')
        for ch in ciphertext:
            if ch.isalpha():
                if ch.isupper():
                    base = base_a
                else:
                    base = base_a_lower
                shifted_char = chr((ord(ch) - base - shift + 26) % 26 + base)
                plaintext.append(shifted_char)
            else:
                plaintext.append(ch)
        return ''.join(plaintext)

    def vigenereDecipher(self, ciphertext: str) -> str:
        decrypted_text = []
        key_index = 0
        key_len = len(self.key)
        base_a = ord('A')
        base_a_lower = ord('a')
        for ch in ciphertext:
            if ch.isalpha():
                shift = ord(self.key[key_index % key_len].lower()) - base_a_lower
                if ch.isupper():
                    base = base_a
                else:
                    base = base_a_lower
                decrypted_char = chr((ord(ch) - base - shift + 26) % 26 + base)
                decrypted_text.append(decrypted_char)
                key_index += 1
            else:
                decrypted_text.append(ch)
        return ''.join(decrypted_text)

    def railFenceDecipher(self, encryptedText: str, rails: int) -> str:
        n = len(encryptedText)
        # Create fence matrix filled with null character (as in Java)
        fence = [['\0' for _ in range(n)] for _ in range(rails)]

        direction = -1
        row = 0
        col = 0

        # Mark positions with '*'
        for i in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row][col] = '*'
            col += 1
            row += direction

        # Fill in the ciphertext in row-major order (only at '*')
        idx = 0
        for i in range(rails):
            for j in range(n):
                if fence[i][j] == '*':
                    fence[i][j] = encryptedText[idx]
                    idx += 1

        # Read the result in zigzag order
        plaintext = []
        direction = -1
        row = 0
        col = 0
        for i in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            plaintext.append(fence[row][col])
            col += 1
            row += direction

        return ''.join(plaintext)