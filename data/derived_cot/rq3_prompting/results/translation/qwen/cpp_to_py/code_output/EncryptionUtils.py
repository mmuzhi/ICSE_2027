class EncryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_cipher(self, plaintext, shift):
        ciphertext = []
        for ch in plaintext:
            if ch.isalpha():
                is_upper = ch.isupper()
                base = ord('a') if not is_upper else ord('A')
                shifted_char = chr((ord(ch.lower()) - base + shift) % 26 + base)
                ciphertext.append(shifted_char if is_upper else shifted_char.lower())
            else:
                ciphertext.append(ch)
        return ''.join(ciphertext)

    def vigenere_cipher(self, plain_text):
        encrypted_text = []
        key_index = 0
        for ch in plain_text:
            if ch.isalpha():
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                base_char = ch.lower()
                shifted_char = chr((ord(base_char) - ord('a') + shift) % 26 + ord('a'))
                encrypted_char = shifted_char if ch.isupper() else shifted_char
                encrypted_text.append(encrypted_char)
                key_index += 1
            else:
                encrypted_text.append(ch)
        return ''.join(encrypted_text)

    def rail_fence_cipher(self, plain_text, rails):
        if rails <= 0:
            raise ValueError("Rails must be greater than zero.")
        fence = [''] * rails
        direction = -1
        row = 0
        for ch in plain_text:
            fence[row] += ch
            if row == 0 or row == rails - 1:
                direction *= -1
            row += direction
        return ''.join(fence)