from typing import List

class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        arr = [0] * (n + 1)
        for lv, ar, seats in bookings:
            arr[lv - 1] += seats
            arr[ar] -= seats
        
        ans = [0] * n
        cur = 0
        for i in range(n):
            cur += arr[i]
            ans[i] = cur
        return ans