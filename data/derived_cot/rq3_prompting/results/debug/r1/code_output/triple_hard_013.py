from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0

        # keep only characters that appear in s2
        s2_set = set(s2)
        s1 = ''.join(c for c in s1 if c in s2_set)

        rec = [0]                     # rec[i] = number of s1 used after i s2 matches
        track = defaultdict(int)      # pointer position -> index in rec
        ct = 0                        # number of times we wrapped around s1
        start = 0
        ptr = 0

        while True:
            for ch in s2:
                ptr = s1.find(ch, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(ch)   # start from the beginning
                start = ptr + 1

            # one full s2 was matched
            rec.append(ct + 1)          # total s1 used so far

            if rec[-1] > n1:           # exceeded available s1 copies
                return (len(rec) - 2) // n2

            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                # cycle detected
                cycle_start_idx = track[ptr]
                cycle_start_s1 = rec[cycle_start_idx]
                cycle_s1_len = ct + 1 - cycle_start_s1
                cycle_s2_len = len(rec) - 1 - cycle_start_idx

                rest_s1 = n1 - cycle_start_s1
                full_cycles = rest_s1 // cycle_s1_len
                rem_s1 = rest_s1 % cycle_s1_len

                total_s2 = cycle_start_idx + full_cycles * cycle_s2_len

                # simulate the remainder part
                target_s1 = cycle_start_s1 + rem_s1
                i = cycle_start_idx + 1
                while i < len(rec) and rec[i] <= target_s1:
                    i += 1
                extra_s2 = i - cycle_start_idx - 1
                total_s2 += extra_s2

                return total_s2 // n2

        # unreachable
        return 0