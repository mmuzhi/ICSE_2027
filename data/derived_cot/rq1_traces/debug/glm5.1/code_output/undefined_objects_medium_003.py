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
            stockBuy = prices[i]
            stockSell = prices[j]
            
            if stockSell - stockBuy < 0:
                i = j
                j = i + 1
            else:
                if j + 1 < len(prices) and prices[j+1] > stockSell:
                    j += 1
                else:
                    profit += stockSell - stockBuy
                    i = j + 1
                    j = i + 1
                    
        return profit