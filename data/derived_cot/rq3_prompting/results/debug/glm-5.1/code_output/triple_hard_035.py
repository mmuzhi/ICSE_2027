class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)): return 0
        
        s1 = ''.join(char for char in s1 if char in set(s2))
        
        rec = [0]
        track = {}
        ct = 0
        start = 0
        
        while True:
            ptr = -1
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    if ct + 1 > n1: return (len(rec)-1)//n2
                    ptr = s1.find(char)
                start = ptr + 1
            rec.append(ct + 1)
            
            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                break
                
        cycleStart = rec[track[ptr]]
        cycle1 = ct + 1 - cycleStart
        cycle2 = len(rec) - 1 - track[ptr]
        rest = n1 - cycleStart
        
        rem = cycleStart + rest % cycle1
        
        ptr2 = 0
        while ptr2 < len(rec) and rec[ptr2] <= rem:
            ptr2 += 1
            
        return (cycle2 * (rest // cycle1) + ptr2 - 1) // n2