class DecryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_decipher(self, ciphertext, shift):
        shift = shift % 26
        plaintext = []
        for char in ciphertext:
            if char.isalpha():
                base = 'A' if char.isupper() else 'a'
                shifted_char = chr((ord(char) - ord(base) - shift + 26) % 26 + ord(base))
                plaintext.append(shifted_char)
            else:
                plaintext.append(char)
        return ''.join(plaintext)

    def vigenere_decipher(self, ciphertext):
        decrypted_text = []
        key_length = len(self.key)
        key_index = 0
        for char in ciphertext:
            if char.isalpha():
                is_upper = char.isupper()
                char_lower = char.lower()
                shift = ord(self.key[key_index % key_length].lower()) - ord('a')
                shifted_char_lower = chr((ord(char_lower) - ord('a') - shift + 26) % 26 + ord('a'))
                if is_upper:
                    shifted_char_upper = shifted_char_lower.upper()
                    decrypted_text.append(shifted_char_upper)
                else:
                    decrypted_text.append(shifted_char_lower)
                key_index += 1
            else:
                decrypted_text.append(char)
        return ''.join(decrypted_text)

    def rail_fence_decipher(self, encrypted_text, rails):
        n = len(encrypted_text)
        if rails <= 1:
            return encrypted_text

        # Create a 2D list (fence) with rails rows and n columns, filled with spaces
        fence = [[' ' for _ in range(n)] for _ in range(rails)]
        
        # Mark the positions with '*'
        direction = -1
        row, col = 0, 0
        for _ in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row][col] = '*'
            col += 1
            row += direction
        
        # Replace the marked positions with characters from encrypted_text
        index = 0
        for r in range(rails):
            for c in range(n):
                if fence[r][c] == '*':
                    fence[r][c] = encrypted_text[index]
                    index += 1
        
        # Read the fence in the zigzag pattern to get plaintext
        direction = -1
        row, col = 0, 0
        plaintext_chars = []
        for _ in range(n):
            if row == 0 or row == rails - 1:
                direction = -direction
            plaintext_chars.append(fence[row][col])
            col += 1
            row += direction
        
        return ''.join(plaintext_chars)