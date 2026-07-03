class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) < 2:
            return 0
        i = 0
        j = 1
        profit = 0
        while j < len(prices):
            if prices[j] < prices[i]:
                i = j
                j += 1
            else:
                if j + 1 < len(prices) and prices[j+1] > prices[j]:
                    j += 1
                else:
                    profit += prices[j] - prices[i]
                    i = j
                    j += 1
        return profit