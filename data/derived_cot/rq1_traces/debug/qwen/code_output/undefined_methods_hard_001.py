from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec = [0]
        track = defaultdict(int)
        start = 0
        ptr = 0
        ptr2 = 0
        
        while True:
            found = False
            for char in s2:
                pos = s1.find(char, start)
                if pos == -1:
                    start = 0
                    pos = s1.find(char)
                    if pos == -1:
                        break
                start = pos + 1
                if start >= len(s1):
                    start = 0
            if start >= len(s1):
                rec.append(len(rec))
            else:
                rec.append(len(rec) + 1)
                found = True
            
            if not found and start >= len(s1):
                if start == 0:
                    rec.append(len(rec))
                else:
                    rec.append(len(rec))
            
            if rec[-1] > n1 * len(s1):
                return (len(rec) - 1) // n2
            
            if start in track:
                cycle_start = track[start]
                cycle_length = len(rec) - cycle_start - 1
                total_occurrences = (n1 * len(s1) // len(s1)) * (rec[cycle_start] - rec[track[start]])
                remaining_chars = n1 * len(s1) % len(s1)
                remaining_occurrences = 0
                for i in range(track[start], len(rec)-1):
                    if rec[i] <= n1 * len(s1):
                        remaining_occurrences += 1
                    else:
                        break
                total_occurrences += remaining_occurrences
                return total_occurrences // n2
            else:
                track[start] = len(rec) - 1
        
        return 0