from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) < 2:
            return 0
        if len(prices) == 2:
            output = prices[1] - prices[0]
            return output if output > 0 else 0
        i = 0
        j = 1
        stockBuy = prices[i]
        stockSell = prices[j]
        profit = 0
        while j < len(prices):
            if stockSell - stockBuy < 0:
                i = j
            else:
                if j + 1 >= len(prices) or prices[j+1] <= stockSell:
                    profit = profit + (stockSell - stockBuy)
                    i = j
            j += 1
            if j < len(prices):
                stockBuy = prices[i]
                stockSell = prices[j]
        return profit