class EncryptionUtils:
    def __init__(self, key: str):
        self.key = key

    def caesar_cipher(self, plaintext: str, shift: int) -> str:
        ciphertext = []
        for ch in plaintext:
            if ch.isalpha():
                ascii_offset = 65 if ch.isupper() else 97
                val = ord(ch.lower()) - ord('a') + shift
                
                # Replicate C++ modulo behavior for negative numbers
                mod_val = val % 26
                if val < 0 and mod_val != 0:
                    mod_val -= 26
                    
                shifted_char = chr(mod_val + ascii_offset)
                ciphertext.append(shifted_char)
            else:
                ciphertext.append(ch)
        return "".join(ciphertext)

    def vigenere_cipher(self, plain_text: str) -> str:
        encrypted_text = []
        key_index = 0
        for ch in plain_text:
            if ch.isalpha():
                shift = ord(self.key[key_index % len(self.key)].lower()) - ord('a')
                val = (ord(ch.lower()) - ord('a') + shift) % 26
                encrypted_char = chr(val + ord('a'))
                if ch.isupper():
                    encrypted_text.append(encrypted_char.upper())
                else:
                    encrypted_text.append(encrypted_char)
                key_index += 1
            else:
                encrypted_text.append(ch)
        return "".join(encrypted_text)

    def rail_fence_cipher(self, plain_text: str, rails: int) -> str:
        if rails <= 0:
            raise ValueError("Rails must be greater than zero.")
        
        # Replicating the fixed size array behavior of the C++ code
        N = 101
        fence = [''] * N
        direction = -1
        row = 0

        for ch in plain_text:
            if row == 0 or row == rails - 1:
                direction = -direction
            
            fence[row] += ch
            row += direction

        encrypted_text = []
        for i in range(rails):
            encrypted_text.append(fence[i])
            
        return "".join(encrypted_text)