from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If any character in s2 is missing from s1, impossible
        if not set(s2).issubset(set(s1)):
            return 0

        # Keep only characters of s1 that appear in s2
        s1 = ''.join(char for char in s1 if char in set(s2))

        # rec[i] = number of s1 repeats used to match i copies of s2
        rec = [0]
        # maps a position in s1 to the index in rec when that position was first seen
        track = defaultdict(int)

        ct = 0          # number of times we started a new s1 repeat (excluding the initial one)
        start = 0       # current search start position in the current s1 repeat

        while True:
            # Match one full s2
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:               # need to move to the next s1 repeat
                    ct += 1
                    ptr = s1.find(char)     # now search from the beginning of the new s1
                start = ptr + 1

            # After finishing one s2 match, record total s1 repeats used so far
            rec.append(ct + 1)

            # If we have exceeded n1 repeats, the last s2 match is incomplete
            if rec[-1] > n1:
                return (len(rec) - 2) // n2

            # Cycle detection: the final position ptr after matching s2
            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                break   # cycle found

        # Extract cycle parameters
        cycle_start_idx = track[ptr]            # index in rec where cycle begins
        pre_repeats = rec[cycle_start_idx]      # s1 repeats used before cycle
        pre_matches = cycle_start_idx           # s2 matches completed before cycle
        cycle1 = (ct + 1) - pre_repeats         # s1 repeats consumed in one full cycle
        cycle2 = len(rec) - 1 - cycle_start_idx # s2 matches in one full cycle

        remaining_repeats = n1 - pre_repeats
        full_cycles = remaining_repeats // cycle1
        remainder = remaining_repeats % cycle1

        # Count how many extra s2 matches fit into the remainder s1 repeats
        extra = 0
        idx = cycle_start_idx + 1
        while idx < len(rec) and rec[idx] - pre_repeats <= remainder:
            extra += 1
            idx += 1

        total_matches = pre_matches + full_cycles * cycle2 + extra
        return total_matches // n2