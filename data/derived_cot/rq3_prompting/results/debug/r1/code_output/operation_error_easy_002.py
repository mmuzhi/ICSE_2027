class Solution:
    def alternateDigitSum(self, n: int) -> int:
        count = 0
        n_str = str(n)
        for i, digit in enumerate(n_str):
            if i % 2 == 0:
                count += int(digit)
            else:
                count -= int(digit)
        return count