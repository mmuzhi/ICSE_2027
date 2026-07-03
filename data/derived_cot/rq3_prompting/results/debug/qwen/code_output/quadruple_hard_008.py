from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec = [0]
        track = defaultdict(int)
        start = 0
        ct = 0
        ptr = 0
        
        while ptr < len(s2):
            char = s2[ptr]
            next_pos = s1.find(char, start)
            if next_pos == -1:
                ct += 1
                next_pos = s1.find(char)
                if next_pos == -1:
                    break
            start = next_pos + 1
            if start >= len(s1):
                ct += 1
                start = 0
            total_matched = ct * len(s1) + next_pos + 1
            rec.append(total_matched)
            if start in track:
                break
            track[start] = len(rec) - 1
            ptr += 1
        
        if ptr >= len(s2):
            return (len(rec) - 1) // n2
        else:
            return 0