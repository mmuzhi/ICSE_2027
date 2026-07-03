class Solution:
    def getMaximumConsecutive(self, coins: List[int]) -> int:
        ans = 1
        for coin in sorted(coins):
            if coin > ans:
                return ans - 1
            ans += coin
        return ans - 1