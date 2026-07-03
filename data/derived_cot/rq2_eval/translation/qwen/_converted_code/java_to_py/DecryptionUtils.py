class DecryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_decipher(self, ciphertext, shift):
        shift %= 26
        plaintext = []
        for char in ciphertext:
            if char.isalpha():
                ascii_offset = ord('A') if char.isupper() else ord('a')
                shifted_char = chr(((ord(char) - ascii_offset - shift) % 26) + ascii_offset)
                plaintext.append(shifted_char)
            else:
                plaintext.append(char)
        return ''.join(plaintext)

    def vigenere_decipher(self, ciphertext):
        decrypted_text = []
        key_index = 0
        for char in ciphertext:
            if char.isalpha():
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                base = ord('A') if char.isupper() else ord('a')
                decrypted_char = chr(((ord(char) - base - shift) % 26) + base)
                decrypted_text.append(decrypted_char)
                key_index += 1
            else:
                decrypted_text.append(char)
        return ''.join(decrypted_text)

    def rail_fence_decipher(self, encrypted_text, rails):
        if rails == 0:
            raise ValueError("Number of rails must be at least 1")
        if encrypted_text == "":
            return ""
        
        fence = [['' for _ in range(len(encrypted_text))] for _ in range(rails)]
        direction = -1
        row, col = 0, 0
        
        for char in encrypted_text:
            fence[row][col] = '*'
            if row == 0 or row == rails - 1:
                direction *= -1
            row += direction
            col += 1
        
        index = 0
        for i in range(rails):
            for j in range(len(encrypted_text)):
                if fence[i][j] == '*':
                    fence[i][j] = encrypted_text[index]
                    index += 1
        
        plaintext = []
        direction = -1
        row, col = 0, 0
        for _ in range(len(encrypted_text)):
            plaintext.append(fence[row][col])
            if row == 0 or row == rails - 1:
                direction *= -1
            row += direction
            col += 1
        
        return ''.join(plaintext)