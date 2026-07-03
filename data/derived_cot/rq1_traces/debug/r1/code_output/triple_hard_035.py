class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        from collections import defaultdict

        if not set(s2).issubset(set(s1)):
            return 0

        s1 = ''.join([char for char in s1 if char in set(s2)])
        rec = [0]
        track = defaultdict(int)
        ct = start = 0

        while True:
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(char)
                start = ptr + 1
            rec.append(ct + 1)

            if rec[-1] > n1:
                return (len(rec) - 2) // n2

            if ptr in track:
                break
            track[ptr] = len(rec) - 1

        cycle_start_idx = track[ptr]
        cycleStart = rec[cycle_start_idx]
        cycle1 = rec[-1] - cycleStart
        cycle2 = len(rec) - 1 - cycle_start_idx
        rest = n1 - cycleStart

        if cycle1 == 0:
            return 0

        full_cycles = rest // cycle1
        remainder = rest % cycle1
        rem = cycleStart + remainder

        ptr2 = 0
        while ptr2 < len(rec) and rec[ptr2] <= rem:
            ptr2 += 1

        total_s2 = (full_cycles * cycle2) + (ptr2 - 1)
        return total_s2 // n2