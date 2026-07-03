class EncryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_cipher(self, plaintext, shift):
        result = []
        for char in plaintext:
            if char.isupper():
                base = 'A'
                shifted_char = chr(((ord(char) - ord(base) + shift) % 26) + ord(base))
                result.append(shifted_char)
            elif char.islower():
                base = 'a'
                shifted_char = chr(((ord(char) - ord(base) + shift) % 26) + ord(base))
                result.append(shifted_char)
            else:
                result.append(char)
        return ''.join(result)

    def vigenere_cipher(self, plaintext):
        result = []
        key_index = 0
        for char in plaintext:
            if char.isupper():
                plain_shift = ord(char) - ord('A')
                key_char = self.key[key_index % len(self.key)]
                key_shift = ord(key_char) - ord('a') if key_char.islower() else ord(key_char) - ord('A')
                shifted_char = chr((plain_shift + key_shift) % 26 + ord('A'))
                result.append(shifted_char)
                key_index += 1
            elif char.islower():
                plain_shift = ord(char) - ord('a')
                key_char = self.key[key_index % len(self.key)]
                key_shift = ord(key_char) - ord('a')
                shifted_char = chr((plain_shift + key_shift) % 26 + ord('a'))
                result.append(shifted_char)
                key_index += 1
            else:
                result.append(char)
        return ''.join(result)

    def rail_fence_cipher(self, plaintext, rails):
        if rails == 0 or rails == 1:
            return plaintext
        
        fence = [['\0' for _ in range(len(plaintext))] for _ in range(rails)]
        direction = -1
        current_row = 0
        col_index = 0
        
        for char in plaintext:
            if current_row == 0 or current_row == rails - 1:
                direction *= -1
            fence[current_row][col_index] = char
            col_index += 1
            current_row += direction
        
        result = []
        for row in range(rails):
            for col in range(len(plaintext)):
                if fence[row][col] != '\0':
                    result.append(fence[row][col])
        return ''.join(result)