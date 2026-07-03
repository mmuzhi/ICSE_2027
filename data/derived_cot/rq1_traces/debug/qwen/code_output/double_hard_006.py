class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        s1 = ''.join(char for char in s1 if char in set(s2))
        if not s2:
            return 0
        
        rec = [0]
        track = {}
        ct = 0
        start = 0
        
        while True:
            for char in s2:
                pos = s1.find(char, start)
                if pos == -1:
                    ct += 1
                    pos = s1.find(char)
                    if pos == -1:
                        return 0
                start = pos + 1
                if start >= len(s1):
                    start = 0
            rec.append(ct + 1)
            if rec[-1] > n1:
                return (len(rec) - 1) // n2
            if start not in track:
                track[start] = len(rec) - 1
            else:
                break
        
        cycleStart = rec[track[start]]
        cycle1 = ct + 1 - cycleStart
        cycle2 = len(rec) - 1 - track[start]
        rest = n1 - cycleStart
        full_cycles = rest // cycle1
        total_occurrences = cycle2 * full_cycles
        
        rem = cycleStart + rest % cycle1
        idx = len(rec) - 1
        while idx >= 0 and rec[idx] > rem:
            idx -= 1
        additional_occurrences = idx
        total_occurrences += additional_occurrences
        
        return total_occurrences // n2