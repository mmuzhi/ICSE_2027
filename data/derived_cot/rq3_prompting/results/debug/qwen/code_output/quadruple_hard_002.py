class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        rec, track = [0], {}
        start = 0
        ptr = 0
        
        while ptr < len(s2):
            found = False
            for i in range(start, len(s1)):
                if s1[i] == s2[ptr]:
                    start = i + 1
                    ptr += 1
                    found = True
                    break
            if not found:
                break
            if ptr == len(s2):
                rec.append(start)
                ptr = 0
        
        if len(rec) == 1:
            return 0
        
        cycle_start_index = None
        for i in range(len(rec) - 1, 0, -1):
            if rec[i] < rec[i-1]:
                cycle_start_index = i - 1
                break
        
        if cycle_start_index is None:
            return (len(rec) - 1) // n2
        
        cycle_start = rec[cycle_start_index]
        cycle_length = rec[-1] - cycle_start
        total_chars = n1 * len(s1)
        cycle_count = (total_chars - cycle_start) // cycle_length
        total_count = cycle_count + (rec[-1] - cycle_start) // cycle_length
        return total_count // n2