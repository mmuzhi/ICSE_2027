import bisect
from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        total_length = n1 * len(s1)
        if not set(s2).issubset(set(s1)):
            return 0
        
        pos_in_s1 = {}
        for char in set(s2):
            pos_in_s1[char] = [i for i, c in enumerate(s1) if c == char]
        
        rec = [0]
        track = defaultdict(int)
        ptr = 0
        start = 0
        ct = 0
        
        while True:
            for char in s2:
                found = False
                while start < total_length:
                    copy_index = start // len(s1)
                    pos_in_current = start % len(s1)
                    arr = pos_in_s1[char]
                    if not arr:
                        break
                    idx = bisect.bisect_left(arr, pos_in_current)
                    if idx < len(arr):
                        start = copy_index * len(s1) + arr[idx] + 1
                        found = True
                        break
                if not found:
                    ct += 1
                    start = 0
                    if start >= total_length:
                        break
            rec.append(ct + len(rec) - 1)
            
            if rec[-1] > total_length:
                return (len(rec) - 2) // n2
            
            if start not in track:
                track[start] = len(rec) - 1
            else:
                cycle_start = rec[track[start]]
                cycle_length = rec[-1] - cycle_start
                total_reps = (total_length - cycle_start) // cycle_length
                remaining = (total_length - cycle_start) % cycle_length
                count = total_reps * (len(s2) // cycle_length) + (1 if remaining >= rec[ptr] else 0)
                return (count + len(rec) - 2) // n2
        
        return 0