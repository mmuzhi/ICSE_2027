from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) < 2:
            return 0
        profit = 0
        i = 0
        j = 1
        while j < len(prices):
            current_buy = prices[i]
            current_sell = prices[j]
            if current_sell < current_buy:
                i = j
                j += 1
            else:
                if j + 1 < len(prices) and prices[j+1] > current_sell:
                    j += 1
                else:
                    profit += current_sell - current_buy
                    i = j + 1
                    j = i + 1
        return profit