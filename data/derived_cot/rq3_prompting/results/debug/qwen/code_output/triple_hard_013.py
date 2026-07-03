from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec = [0]
        track = defaultdict(int)
        ct = 0
        start = 0
        
        for char in s2:
            while True:
                pos = s1.find(char, start)
                if pos == -1:
                    ct += 1
                    start = 0
                    pos = s1.find(char)
                    if pos == -1:
                        break
                start = pos + 1
                total_chars = ct * len(s1) + pos + 1
                if total_chars > rec[-1]:
                    rec.append(total_chars)
                break
        
        if len(rec) <= 1:
            return 0
        
        cycle_start = track[rec[-1]]
        cycle_length = len(rec) - track[rec[-1]]
        base = cycle_start
        
        total_occurrences = base + (n1 * len(s1) - base) // (cycle_length // (len(s2)))
        
        return total_occurrences // n2