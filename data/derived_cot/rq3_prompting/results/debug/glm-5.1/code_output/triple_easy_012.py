class Solution:
    def alternateDigitSum(self, n: int) -> int:
        result = str(n)
        ans = 0
        for i in range(len(result)):
            if i % 2 == 0:
                ans += int(result[i])
            else:
                ans -= int(result[i])
        return ans