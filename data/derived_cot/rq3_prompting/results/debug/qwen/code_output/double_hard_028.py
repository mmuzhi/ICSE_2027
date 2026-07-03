from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec = [0]
        track = defaultdict(int)
        start = 0
        total_occurrences = 0
        
        while True:
            for char in s2:
                pos = s1.find(char, start)
                if pos == -1:
                    pos = s1.find(char)
                    start = 0 if pos != -1 else start
                if pos == -1:
                    break
                start = pos + 1
            else:
                total_occurrences += 1
                rec.append(total_occurrences)
                if start in track:
                    cycle_start_index = track[start]
                    cycle_length = len(rec) - cycle_start_index - 1
                    cycle_occurrences = total_occurrences - rec[cycle_start_index]
                    break
                track[start] = len(rec) - 1
                continue
            
            rec.append(total_occurrences)
            if start in track:
                cycle_start_index = track[start]
                cycle_length = len(rec) - cycle_start_index - 1
                cycle_occurrences = total_occurrences - rec[cycle_start_index]
                break
        
        full_cycles = (n1 - cycle_start_index) // cycle_length
        total_occurrences += full_cycles * cycle_occurrences
        
        return total_occurrences // n2