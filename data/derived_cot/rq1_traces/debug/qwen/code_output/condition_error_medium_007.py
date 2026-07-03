class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        arr = [0] * (n + 2)
        for s, e, seats in bookings:
            arr[s] += seats
            arr[e + 1] -= seats
        for i in range(1, n + 1):
            arr[i] += arr[i - 1]
        return arr[:n]