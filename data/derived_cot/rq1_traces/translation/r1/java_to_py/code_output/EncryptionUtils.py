class EncryptionUtils:
    def __init__(self, key):
        self.key = key

    def caesarCipher(self, plaintext, shift):
        result = []
        base_upper = ord('A')
        base_lower = ord('a')
        for char in plaintext:
            if char.isalpha():
                if char.isupper():
                    base = base_upper
                else:
                    base = base_lower
                total = ord(char) - base + shift
                mod = total % 26
                if total < 0 and mod != 0:
                    mod -= 26
                shifted_char = chr(mod + base)
                result.append(shifted_char)
            else:
                result.append(char)
        return ''.join(result)

    def vigenereCipher(self, plainText):
        result = []
        key_index = 0
        key = self.key
        for char in plainText:
            if char.isalpha():
                key_char = key[key_index % len(key)]
                shift = ord(key_char.lower()) - ord('a')
                if char.islower():
                    base = ord('a')
                    new_char = chr((ord(char) - base + shift) % 26 + base)
                    result.append(new_char)
                else:
                    base = ord('a')
                    new_char = chr((ord(char.lower()) - base + shift) % 26 + base)
                    result.append(new_char.upper())
                key_index += 1
            else:
                result.append(char)
        return ''.join(result)

    def railFenceCipher(self, plainText, rails):
        n = len(plainText)
        fence = [['\n'] * n for _ in range(rails)]
        direction = -1
        row, col = 0, 0
        
        for char in plainText:
            if row == 0 or row == rails - 1:
                direction = -direction
            fence[row][col] = char
            col += 1
            row += direction
        
        result = []
        for i in range(rails):
            for j in range(n):
                if fence[i][j] != '\n':
                    result.append(fence[i][j])
        return ''.join(result)