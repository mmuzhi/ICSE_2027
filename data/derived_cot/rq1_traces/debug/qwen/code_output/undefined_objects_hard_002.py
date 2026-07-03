class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        start, end = min(stations), sum(stations) + k
        while start + 1 < end:
            mid = (start + end) // 2
            if self.check(stations, r, k, mid):
                start = mid
            else:
                end = mid
        if self.check(stations, r, k, end):
            return end
        else:
            return start

    def check(self, stations, r, k, target):
        n = len(stations)
        if n == 0:
            return True
        add = [0] * n
        remaining = k
        cur = 0
        # Build the initial window for station0: [0, r] (if exists)
        cur_window = 0
        window_size = min(r+1, n)
        for i in range(window_size):
            cur_window += stations[i]
        if cur_window < target:
            deficit = target - cur_window
            if deficit > remaining:
                return False
            add[window_size-1] += deficit
            remaining -= deficit
            cur_window += deficit
        
        # For stations from 1 to n-1
        for i in range(1, n):
            # Remove the station that is leaving the window: station[i-1]
            if i-1 < window_size:
                cur_window -= stations[i-1] + add[i-1]
            else:
                cur_window -= stations[i-1]
            # Add the station that is entering the window: station[i+r] if exists
            if i+r < n:
                cur_window += stations[i+r] + add[i+r]
            else:
                cur_window += stations[i+r] if i+r < n else 0
            if cur_window < target:
                deficit = target - cur_window
                if deficit > remaining:
                    return False
                # Add the deficit to the last station in the window
                last_index = i+r if i+r < n else n-1
                add[last_index] += deficit
                remaining -= deficit
                cur_window += deficit
        return True