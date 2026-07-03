class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if n1 == 0:
            return 0
            
        rec, track = [0], {}
        ct = start = 0

        if not set(s2).issubset(set(s1)): 
            return 0

        s1 = ''.join(char for char in s1 if char in set(s2))
        
        while True:
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(char)
                start = ptr + 1
            rec.append(ct + 1)

            if rec[-1] > n1:
                return (len(rec) - 2) // n2
            if rec[-1] == n1:
                return (len(rec) - 1) // n2

            if start not in track: 
                track[start] = len(rec) - 1
            else: 
                break
        
        cycleStartIdx = track[start]
        cycle1 = rec[-1] - rec[cycleStartIdx]
        cycle2 = len(rec) - 1 - cycleStartIdx
        rest = n1 - rec[cycleStartIdx]
        
        ans = cycle2 * (rest // cycle1) + cycleStartIdx
        rem = rest % cycle1
        
        ptr2 = cycleStartIdx
        while ptr2 < len(rec) and rec[ptr2] <= rec[cycleStartIdx] + rem:
            ptr2 += 1
        ptr2 -= 1
        
        return (ans + ptr2 - cycleStartIdx) // n2