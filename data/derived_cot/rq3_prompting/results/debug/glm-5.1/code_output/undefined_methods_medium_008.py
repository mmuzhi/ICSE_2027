class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:

        arr = [0]*(n+1)
        for lv, ar, seats in bookings:
            arr[lv-1]+= seats
            arr[ar]-= seats

        res = arr[:-1]
        for i in range(1, n):
            res[i] += res[i-1]
        return res