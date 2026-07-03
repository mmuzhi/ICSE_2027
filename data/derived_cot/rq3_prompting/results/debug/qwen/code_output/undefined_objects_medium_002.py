class Solution:
    def minOperationsMaxProfit(self, customers: List[int], boardingCost: int, runningCost: int) -> int:
        maxProfit = -1
        ans = 0
        i = 0
        curRounds = 0
        curCustomers = 0
        rem = 0
        while i < len(customers) or rem:
            if i < len(customers):
                rem += customers[i]
                i += 1
            curRounds += 1
            if rem >= 4:
                rem -= 4
                curCustomers += 4
            else:
                curCustomers += rem
                rem = 0
            curProfit = (curCustomers * boardingCost) - (curRounds * runningCost)
            if curProfit > maxProfit:
                maxProfit = curProfit
                ans = curRounds
        return ans if maxProfit > 0 else -1