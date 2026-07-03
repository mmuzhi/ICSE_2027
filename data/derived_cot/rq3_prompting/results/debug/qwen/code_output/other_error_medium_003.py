class Solution:
    def getMaximumConsecutive(self, coins: List[int]) -> int:
        if not coins:
            return 0
        
        coins_sorted = sorted(coins)
        if coins_sorted[0] != 1:
            return 0
        
        ans = 1
        for coin in coins_sorted:
            if coin > ans:
                return ans
            ans += coin
        
        return ans