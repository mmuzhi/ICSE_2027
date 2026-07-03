class Solution:
    def alternateDigitSum(self, n: int) -> int:
        n_abs = abs(n)
        n_str = str(n_abs)
        count = 0
        for i in range(len(n_str)):
            if i % 2 == 0:
                count += int(n_str[i])
            else:
                count -= int(n_str[i])
        return count