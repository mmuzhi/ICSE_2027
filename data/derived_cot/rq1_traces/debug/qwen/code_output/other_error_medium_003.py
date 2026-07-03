class Solution:
    def getMaximumConsecutive(self, coins: List[int]) -> int:
        coins_sorted = sorted(coins)
        ans = 0
        for coin in coins_sorted:
            if coin > ans + 1:
                break
            ans += coin
        return ans + 1