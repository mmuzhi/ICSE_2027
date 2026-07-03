class EncryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesar_cipher(self, plaintext, shift):
        ciphertext = []
        for ch in plaintext:
            if ch.isalpha():
                ascii_offset = 65 if ch.isupper() else 97
                base_char = ch.lower()
                shifted_char = chr((ord(base_char) - 97 + shift) % 26 + 97)
                shifted_char = shifted_char.upper() if ch.isupper() else shifted_char
                ciphertext.append(shifted_char)
            else:
                ciphertext.append(ch)
        return ''.join(ciphertext)

    def vigenere_cipher(self, plain_text):
        encrypted_text = []
        key_index = 0
        for ch in plain_text:
            if ch.isalpha():
                shift_char = self.key[key_index % len(self.key)]
                shift = ord(shift_char.lower()) - 97
                base_char = ch.lower()
                shifted_char = chr((ord(base_char) - 97 + shift) % 26 + 97)
                shifted_char = shifted_char.upper() if ch.isupper() else shifted_char
                encrypted_text.append(shifted_char)
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
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row] += ch
            row += direction
        return ''.join(fence)