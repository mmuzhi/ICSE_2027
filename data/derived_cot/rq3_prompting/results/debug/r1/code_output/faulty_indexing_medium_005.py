class Solution:
    def decodeCiphertext(self, encoded_text: str, rows: int) -> str:
        if rows == 1:
            return encoded_text

        n = len(encoded_text)
        cols = (n + rows - 1) // rows          # ceil division
        # Build the grid by placing characters in diagonal order
        grid = [[''] * cols for _ in range(rows)]
        idx = 0
        for s in range(rows + cols - 1):      # each diagonal (sum of row and col)
            # rows in this diagonal: from max(0, s-cols+1) to min(rows-1, s)
            for r in range(max(0, s - cols + 1), min(rows, s + 1)):
                c = s - r
                if idx < n:
                    grid[r][c] = encoded_text[idx]
                    idx += 1

        # Read the grid row by row
        result = []
        for r in range(rows):
            for c in range(cols):
                if grid[r][c]:                # only non-empty cells
                    result.append(grid[r][c])
        return ''.join(result).rstrip()