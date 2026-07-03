class EncryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_cipher(self, plaintext, shift):
        result = []
        for char in plaintext:
            if char.isupper():
                shifted_char = chr(((ord(char) - ord('A') + shift) % 26) + ord('A'))
                result.append(shifted_char)
            elif char.islower():
                shifted_char = chr(((ord(char) - ord('a') + shift) % 26) + ord('a'))
                result.append(shifted_char)
            else:
                result.append(char)
        return ''.join(result)

    def vigenere_cipher(self, plaintext):
        result = []
        key_index = 0
        for char in plaintext:
            if char.isupper():
                key_char = self.key[key_index % len(self.key)].upper()
                shift = ord(key_char) - ord('A')
                encrypted_char = chr(((ord(char) - ord('A') + shift) % 26) + ord('A'))
                result.append(encrypted_char)
                key_index += 1
            elif char.islower():
                key_char = self.key[key_index % len(self.key)].lower()
                shift = ord(key_char) - ord('a')
                encrypted_char = chr(((ord(char) - ord('a') + shift) % 26) + ord('a'))
                result.append(encrypted_char)
                key_index += 1
            else:
                result.append(char)
        return ''.join(result)

    def rail_fence_cipher(self, plaintext, rails):
        fence = [['\n' for _ in range(len(plaintext))] for _ in range(rails)]
        direction = -1
        row, col = 0, 0
        
        for char in plaintext:
            if row == 0 or row == rails - 1:
                direction *= -1
            fence[row][col] = char
            col += 1
            row += direction
            
        result = []
        for i in range(rails):
            for j in range(len(plaintext)):
                if fence[i][j] != '\n':
                    result.append(fence[i][j])
        return ''.join(result)