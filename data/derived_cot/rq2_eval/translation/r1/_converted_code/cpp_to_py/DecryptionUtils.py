class DecryptionUtils:
    def __init__(self, key: str):
        self.key = key

    def caesar_decipher(self, ciphertext: str, shift: int) -> str:
        shift = shift % 26
        if shift < 0:
            shift += 26
        plaintext = []
        for char in ciphertext:
            if char.isalpha():
                base = 'A' if char.isupper() else 'a'
                shifted_char = chr((ord(char) - ord(base) - shift + 26) % 26 + ord(base))
                plaintext.append(shifted_char)
            else:
                plaintext.append(char)
        return ''.join(plaintext)

    def vigenere_decipher(self, ciphertext: str) -> str:
        key = self.key
        key_length = len(key)
        decrypted_text = []
        key_index = 0
        for char in ciphertext:
            if char.isalpha():
                shift_char = key[key_index % key_length]
                shift = ord(shift_char.lower()) - ord('a')
                if char.islower():
                    decrypted_char = chr((ord(char) - ord('a') - shift + 26) % 26 + ord('a'))
                else:
                    decrypted_char = chr((ord(char.lower()) - ord('a') - shift + 26) % 26 + ord('a')).upper()
                decrypted_text.append(decrypted_char)
                key_index += 1
            else:
                decrypted_text.append(char)
        return ''.join(decrypted_text)

    def rail_fence_decipher(self, encrypted_text: str, rails: int) -> str:
        n = len(encrypted_text)
        if rails <= 1:
            return encrypted_text
        
        fence = [[''] * n for _ in range(rails)]
        
        direction = -1
        row = 0
        col = 0
        for i in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row][col] = '*'
            col += 1
            row += direction
        
        index = 0
        for r in range(rails):
            for c in range(n):
                if fence[r][c] == '*':
                    fence[r][c] = encrypted_text[index]
                    index += 1
        
        direction = -1
        row = 0
        col = 0
        plain_text = []
        for i in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            plain_text.append(fence[row][col])
            col += 1
            row += direction
        
        return ''.join(plain_text)