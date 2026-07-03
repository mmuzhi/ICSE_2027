class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        arr = [0] * (n + 2)
        for first, last, seats in bookings:
            arr[first - 1] += seats
            arr[last] -= seats
        res = []
        total = 0
        for i in range(n):
            total += arr[i]
            res.append(total)
        return res