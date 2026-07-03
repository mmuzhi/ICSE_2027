from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return n1
        if not s1:
            return 0
        
        rec = [0]
        track = defaultdict(int)
        ct = start = ptr = ptr2 = 0

        if not set(s2).issubset(set(s1)):
            return 0

        s1 = ''.join(char for char in s1 if char in set(s2))
        
        while True:
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(char)
                    if ptr == -1:
                        return 0
                start = ptr + 1
            rec.append(ct + 1)
            
            if rec[-1] >= n1:
                return (len(rec) - 1) // n2

            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                break
        
        cycle_start_index = track[ptr]
        cycle_start = rec[cycle_start_index]
        cycle_length = len(rec) - cycle_start_index
        cycle_char = s2[-1]
        
        remaining = n1 - cycle_start
        
        full_cycles = remaining // cycle_length
        remainder = remaining % cycle_length
        
        total_occurrences = cycle_start + full_cycles * cycle_length + remainder
        
        return (total_occurrences // len(s2)) // n2