from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec = [0]
        track = defaultdict(int)
        ct = 0
        start = 0
        
        while True:
            found = True
            for char in s2:
                pos = s1.find(char, start)
                if pos == -1:
                    found = False
                    break
                start = pos + 1
                ct += 1
            
            rec.append(ct)
            
            if ct > n1 * len(s1):
                break
            
            if start in track:
                cycleStart = rec[track[start]]
                cycle1 = ct - cycleStart
                cycle2 = len(rec) - 1 - track[start]
                
                remaining_chars = n1 * len(s1) - cycleStart
                full_cycles = remaining_chars // cycle1
                additional_s2 = full_cycles * cycle2
                
                total_s2 = (len(rec) - 1) + additional_s2
                return total_s2 // n2
            else:
                track[start] = len(rec) - 1
        
        total_s2 = (len(rec) - 1)
        return total_s2 // n2