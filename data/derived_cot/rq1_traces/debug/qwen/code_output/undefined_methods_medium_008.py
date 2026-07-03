class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        arr = [0] * (n + 1)
        for lv, ar, seats in bookings:
            arr[lv - 1] += seats
            arr[ar] -= seats
        
        res = [0] * n
        current = 0
        for i in range(n):
            current += arr[i]
            res[i] = current
        
        return res