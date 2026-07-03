class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        s1 = ''.join(char for char in s1 if char in set(s2))
        if not s1 or not s2:
            return 0
        
        track = {}
        rec = [0]
        ct = 0
        start = 0
        
        while True:
            found = False
            for char in s2:
                pos_in_s1 = s1.find(char, start)
                if pos_in_s1 == -1:
                    break
                start = pos_in_s1 + 1
                found = True
            if found:
                rec.append(ct + 1)
                if rec[-1] >= n1:
                    return (len(rec) - 1) // n2
                if start not in track:
                    track[start] = len(rec) - 1
                else:
                    cycle_start = rec[track[start]]
                    cycle_length = rec[-1] - cycle_start
                    rest = n1 - start
                    num_cycles = rest // cycle_length
                    total_occurrences = num_cycles * cycle_length + (rec[-1] - start)
                    return (total_occurrences) // n2
            else:
                ct += 1
                start = 0
                if start in track:
                    cycle_start = rec[track[start]]
                    cycle_length = rec[-1] - cycle_start
                    rest = n1 - start
                    num_cycles = rest // cycle_length
                    total_occurrences = num_cycles * cycle_length + (rec[-1] - start)
                    return (total_occurrences) // n2