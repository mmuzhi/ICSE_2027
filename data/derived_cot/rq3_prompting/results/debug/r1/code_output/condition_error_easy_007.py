from typing import List

class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        if numRows == 0:
            return []
        if numRows == 1:
            return [[1]]
        prev = self.generate(numRows - 1)
        last_row = prev[-1]
        new_row = [1]
        for i in range(len(last_row) - 1):
            new_row.append(last_row[i] + last_row[i+1])
        new_row.append(1)
        prev.append(new_row)
        return prev