class DecryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesarDecipher(self, ciphertext, shift):
        shift = shift % 26
        plaintext_chars = []
        for ch in ciphertext:
            if ch.isalpha():
                ascii_offset = 'A' if ch.isupper() else 'a'
                base_ord = ord(ascii_offset)
                shifted_char = chr((ord(ch) - base_ord - shift + 26) % 26 + base_ord)
                plaintext_chars.append(shifted_char)
            else:
                plaintext_chars.append(ch)
        return ''.join(plaintext_chars)

    def vigenereDecipher(self, ciphertext):
        plaintext_chars = []
        key_index = 0
        for ch in ciphertext:
            if ch.isalpha():
                current_key_char = self.key[key_index % len(self.key)]
                shift = ord(current_key_char.lower()) - ord('a')
                ascii_offset = 'A' if ch.isupper() else 'a'
                base_ord = ord(ascii_offset)
                decrypted_char = chr((ord(ch) - base_ord - shift + 26) % 26 + base_ord)
                plaintext_chars.append(decrypted_char)
                key_index += 1
            else:
                plaintext_chars.append(ch)
        return ''.join(plaintext_chars)

    def railFenceDecipher(self, encryptedText, rails):
        n = len(encryptedText)
        fence = [[None] * n for _ in range(rails)]
        
        direction = -1
        row, col = 0, 0
        
        for _ in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row][col] = '*'
            col += 1
            row += direction
        
        index = 0
        for i in range(rails):
            for j in range(n):
                if fence[i][j] == '*':
                    fence[i][j] = encryptedText[index]
                    index += 1
        
        decrypted_chars = []
        direction = -1
        row, col = 0, 0
        for _ in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            decrypted_chars.append(fence[row][col])
            col += 1
            row += direction
        
        return ''.join(decrypted_chars)