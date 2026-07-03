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
        counter = 0
        
        while counter < len(prices) - 2:
            if stockSell - stockBuy < 0:
                i = counter + 1
                j = i + 1
            else:
                if j + 1 < len(prices) and prices[j+1] > prices[j]:
                    j += 1
                else:
                    profit += stockSell - stockBuy
                    i = j + 1
                    j = i + 1
                    if j >= len(prices):
                        break
            
            stockBuy = prices[i]
            stockSell = prices[j]
            counter += 1
        
        if j < len(prices) and stockSell - stockBuy > 0:
            profit += stockSell - stockBuy
        
        return profit