class EncryptionUtils:
    def __init__(self, key):
        self.key = key

    @staticmethod
    def _java_mod(a, b):
        """
        Emulates Java's modulo behavior, which can return negative values 
        if the dividend is negative, unlike Python's modulo which always 
        returns a non-negative result for a positive divisor.
        """
        mod_val = a % b
        if a < 0 and mod_val != 0:
            mod_val -= b
        return mod_val

    def caesar_cipher(self, plaintext, shift):
        ciphertext = []
        for c in plaintext:
            if c.isalpha():
                ascii_offset = ord('A') if c.isupper() else ord('a')
                shifted_val = ord(c) - ascii_offset + shift
                mod_val = self._java_mod(shifted_val, 26)
                ciphertext.append(chr(mod_val + ascii_offset))
            else:
                ciphertext.append(c)
        return "".join(ciphertext)

    def vigenere_cipher(self, plain_text):
        encrypted_text = []
        key_index = 0
        for c in plain_text:
            if c.isalpha():
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                shifted_val = ord(c.lower()) - ord('a') + shift
                mod_val = self._java_mod(shifted_val, 26)
                encrypted_char = chr(mod_val + ord('a'))
                encrypted_text.append(encrypted_char.upper() if c.isupper() else encrypted_char)
                key_index += 1
            else:
                encrypted_text.append(c)
        return "".join(encrypted_text)

    def rail_fence_cipher(self, plain_text, rails):
        if rails < 0:
            raise ValueError("rails cannot be negative")
        
        fence = [['\n'] * len(plain_text) for _ in range(rails)]
        direction = -1
        row, col = 0, 0

        for c in plain_text:
            if row == 0 or row == rails - 1:
                direction = -direction
            
            fence[row][col] = c
            col += 1
            row += direction

        encrypted_text = []
        for i in range(rails):
            for j in range(len(plain_text)):
                if fence[i][j] != '\n':
                    encrypted_text.append(fence[i][j])
        return "".join(encrypted_text)