class EncryptionUtils:
    def __init__(self, key: str):
        self.key = key

    def caesar_cipher(self, plaintext: str, shift: int) -> str:
        ciphertext = []
        for c in plaintext:
            if c.isalpha():
                ascii_offset = ord('A') if c.isupper() else ord('a')
                shifted = chr((ord(c) - ascii_offset + shift) % 26 + ascii_offset)
                ciphertext.append(shifted)
            else:
                ciphertext.append(c)
        return ''.join(ciphertext)

    def vigenere_cipher(self, plain_text: str) -> str:
        encrypted = []
        key_index = 0
        for c in plain_text:
            if c.isalpha():
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                encrypted_char = chr((ord(c.lower()) - ord('a') + shift) % 26 + ord('a'))
                if c.isupper():
                    encrypted_char = encrypted_char.upper()
                encrypted.append(encrypted_char)
                key_index += 1
            else:
                encrypted.append(c)
        return ''.join(encrypted)

    def rail_fence_cipher(self, plain_text: str, rails: int) -> str:
        fence = [['\n'] * len(plain_text) for _ in range(rails)]
        direction = -1
        row = 0
        col = 0
        for c in plain_text:
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row][col] = c
            col += 1
            row += direction
        encrypted = []
        for i in range(rails):
            for j in range(len(plain_text)):
                if fence[i][j] != '\n':
                    encrypted.append(fence[i][j])
        return ''.join(encrypted)