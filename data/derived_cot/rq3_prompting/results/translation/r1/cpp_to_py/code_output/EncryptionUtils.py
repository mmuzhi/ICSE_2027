class EncryptionUtils:
    def __init__(self, key: str) -> None:
        self.key = key

    # ---- Caesar Cipher ----
    def caesar_cipher(self, plaintext: str, shift: int) -> str:
        # Mimics C++ integer modulus (sign follows dividend)
        def cpp_mod(a: int, b: int) -> int:
            r = a % b
            if a < 0 and r != 0:
                r -= b
            return r

        result = []
        for ch in plaintext:
            if ch.isalpha():
                base = ord(ch.lower()) - ord('a')
                shifted = cpp_mod(base + shift, 26)
                offset = 65 if ch.isupper() else 97
                result.append(chr(shifted + offset))
            else:
                result.append(ch)
        return ''.join(result)

    # ---- Vigenère Cipher ----
    def vigenere_cipher(self, plain_text: str) -> str:
        result = []
        key_index = 0
        key_len = len(self.key)
        for ch in plain_text:
            if ch.isalpha():
                shift = ord(self.key[key_index % key_len].lower()) - ord('a')
                base = ord(ch.lower()) - ord('a')
                encrypted_code = (base + shift) % 26 + ord('a')
                encrypted_char = chr(encrypted_code)
                if ch.isupper():
                    result.append(encrypted_char.upper())
                else:
                    result.append(encrypted_char)
                key_index += 1
            else:
                result.append(ch)
        return ''.join(result)

    # ---- Rail Fence Cipher ----
    def rail_fence_cipher(self, plain_text: str, rails: int) -> str:
        if rails <= 0:
            raise ValueError("Rails must be greater than zero.")

        # dynamic list (mimics C++ fixed-size array, but avoids overflow)
        fence = []
        direction = -1
        row = 0

        for ch in plain_text:
            if row == 0 or row == rails - 1:
                direction = -direction
            # ensure the row exists
            while row >= len(fence):
                fence.append('')
            fence[row] += ch
            row += direction

        # only the first 'rails' rows are concatenated
        return ''.join(fence[:rails])