from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        s1 = ''.join([c for c in s1 if c in set(s2)])
        
        rec = [0]
        track = defaultdict(int)
        ct = 0
        start = 0
        
        while True:
            initial_start = start
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(char)
                    if ptr == -1:
                        return 0
                start = ptr + 1
            rec.append(ct + 1)
            
            if rec[-1] > n1:
                return (len(rec) - 2) // n2
            
            if initial_start in track:
                cycleStartIndex = track[initial_start]
                break
            else:
                track[initial_start] = len(rec) - 1
        
        cycleStart = rec[cycleStartIndex]
        cycle1 = rec[-1] - cycleStart
        cycle2 = len(rec) - 1 - cycleStartIndex
        
        if cycle1 == 0:
            return 0
        
        rest = n1 - cycleStart
        q, r = divmod(rest, cycle1)
        rem = cycleStart + r
        
        ptr2 = 0
        while ptr2 < len(rec) and rec[ptr2] <= rem:
            ptr2 += 1
        ptr2 -= 1
        
        total_s2 = cycle2 * q + ptr2
        return total_s2 // n2