class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        from collections import defaultdict

        if n2 == 0:
            return 0

        s2_chars = set(s2)
        if not s2_chars.issubset(set(s1)):
            return 0

        s1 = ''.join([char for char in s1 if char in s2_chars])

        rec = [0]
        track = defaultdict(int)
        ct = start = 0

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

            if rec[-1] > n1:
                return (len(rec) - 2) // n2
            elif rec[-1] == n1:
                return (len(rec) - 1) // n2

            if start in track:
                break
            track[start] = len(rec) - 1

        cycle_start_idx = track[start]
        cycle_s1 = rec[cycle_start_idx]
        cycle_length_s1 = rec[-1] - cycle_s1
        cycle_length_s2 = len(rec) - 1 - cycle_start_idx

        remaining_s1 = n1 - cycle_s1
        num_cycles = remaining_s1 // cycle_length_s1
        remainder_s1 = remaining_s1 % cycle_length_s1

        total_s2 = num_cycles * cycle_length_s2
        remainder_total_s1 = cycle_s1 + remainder_s1

        ptr2 = 0
        while ptr2 < len(rec) and rec[ptr2] <= remainder_total_s1:
            ptr2 += 1
        total_s2 += ptr2 - 1

        return total_s2 // n2