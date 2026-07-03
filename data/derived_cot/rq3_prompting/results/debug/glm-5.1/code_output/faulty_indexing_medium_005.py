class Solution:
    def decodeCiphertext(self, encoded_text: str, rows: int) -> str:
        N = len(encoded_text)
        cols = N // rows
        original_text = []

        for j in range(cols):
            for i in range(rows):
                if i + j < cols:
                    original_text.append(encoded_text[i * (cols + 1) + j])

        return ''.join(original_text).rstrip()