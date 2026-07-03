class Solution:
    def decodeCiphertext(self, encoded_text: str, rows: int) -> str:
        if rows == 1:
            return encoded_text

        N = len(encoded_text)
        cols = N // rows
        i, j, k = 0, 0, 0
        original_text = []

        while k < N:
            original_text.append(encoded_text[k])
            i += 1
            if i >= rows or (j + i) >= cols:
                i = 0
                j += 1
                if j >= cols:
                    break
            k = i * cols + (j + i)

        return ''.join(original_text).rstrip()