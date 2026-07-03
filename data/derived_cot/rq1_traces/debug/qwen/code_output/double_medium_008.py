from typing import List
from itertools import accumulate

class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        arr = [0] * (n + 2)
        for booking in bookings:
            l, r, seats = booking
            arr[l] += seats
            if r + 1 < len(arr):
                arr[r + 1] -= seats
        result = list(accumulate(arr))
        return result[1:1 + n]