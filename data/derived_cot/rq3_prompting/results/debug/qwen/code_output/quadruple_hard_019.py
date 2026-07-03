from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec = [0]
        track = defaultdict(int)
        start = 0
        ptr = 0
        
        while True:
            for char in s2:
                idx = s1.find(char, start)
                if idx == -1:
                    idx = s1.find(char)
                    start = idx + 1 if idx != -1 else -1
                else:
                    start = idx + 1
                if start == -1:
                    break
            rec.append(start)
            if rec[-1] >= n1 * len(s1):
                return (len(rec) - 1) // n2
            if start not in track:
                track[start] = len(rec) - 1
            else:
                cycle_start = track[start]
                cycle_length = len(rec) - cycle_start - 1
                full_cycles = (n1 * len(s1) - rec[cycle_start]) // cycle_length
                total_chars = rec[cycle_start] + full_cycles * cycle_length
                remaining = total_chars % cycle_length
                if remaining > 0:
                    total_chars += remaining
                return (total_chars // len(s2)) // n2
        return 0