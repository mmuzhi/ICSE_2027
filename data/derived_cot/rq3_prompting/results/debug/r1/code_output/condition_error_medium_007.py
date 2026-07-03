from typing import List
from itertools import accumulate

class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        # difference array of length n+1 to handle subtraction at index n
        arr = [0] * (n + 1)
        for lv, ar, seats in bookings:
            # add seats at start index (0-based)
            arr[lv - 1] += seats
            # subtract seats just after the end (index ar, 0-based)
            arr[ar] -= seats
        # prefix sum over the first n elements (flights 1..n)
        return list(accumulate(arr[:n]))