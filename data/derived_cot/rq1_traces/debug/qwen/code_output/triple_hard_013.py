from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        if s2 == "":
            return 0
        
        ptr = 0
        cur = 0
        count = 0
        rec = [0]
        track = defaultdict(int)
        
        while ptr < n1 * len(s1):
            if cur == len(s2):
                count += 1
                cur = 0
                rec.append(count)
            if s2[cur] == s1[ptr % len(s1)]:
                cur += 1
                state = ptr % len(s1)
                if state in track:
                    cycle_start_index = track[state]
                    cycle_length = len(rec) - cycle_start_index
                    total_chars = n1 * len(s1)
                    base = rec[cycle_start_index]
                    step = (ptr - rec[cycle_start_index]) // (count - cycle_start_index)
                    remaining_chars = total_chars - base
                    additional_s2 = remaining_chars // step
                    count += additional_s2
                    break
                else:
                    track[state] = len(rec) - 1
                ptr += 1
            else:
                ptr += 1
        
        return count // n2