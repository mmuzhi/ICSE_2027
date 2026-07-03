class Solution:
    def alternateDigitSum(self, n: int) -> int:
        s = str(abs(n))
        alt_sum = 0
        for i, char in enumerate(s):
            if i % 2 == 0:
                alt_sum += int(char)
            else:
                alt_sum -= int(char)
        return abs(alt_sum)