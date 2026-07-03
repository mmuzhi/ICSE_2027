from typing import List

class Solution:
    def minOperationsMaxProfit(self, customers: List[int], boardingCost: int, runningCost: int) -> int:
        max_profit = -1
        ans = i = current_rounds = current_customers = remaining = 0
        while i < len(customers) or remaining:
            if i < len(customers):
                remaining += customers[i]
                i += 1
            current_rounds += 1
            boarded = min(4, remaining)
            current_customers += boarded
            remaining -= boarded
            profit = current_customers * boardingCost - current_rounds * runningCost
            if profit > max_profit:
                max_profit = profit
                ans = current_rounds
        return ans if max_profit > 0 else -1