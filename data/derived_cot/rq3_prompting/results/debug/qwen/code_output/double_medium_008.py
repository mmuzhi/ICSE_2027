from typing import List
from itertools import accumulate

class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        arr = [0] * (n + 1)
        for lv, ar, seats in bookings:
            arr[lv] += seats
            if ar + 1 <= n:
                arr[ar + 1] -= seats
        return list(accumulate(arr))[1:]