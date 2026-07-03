class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) < 2:
            return 0
        i = 0
        j = 1
        stockBuy = prices[i]
        stockSell = prices[j]
        profit = 0
        while j < len(prices):
            if stockSell - stockBuy < 0:
                i = j
                j = i + 1
            else:
                if j + 1 < len(prices) and prices[j+1] > prices[j]:
                    j += 1
                else:
                    profit = profit + (stockSell - stockBuy)
                    i = j
                    j = i + 1

            if j < len(prices):
                stockSell = prices[j]
                stockBuy = prices[i]
        return profit