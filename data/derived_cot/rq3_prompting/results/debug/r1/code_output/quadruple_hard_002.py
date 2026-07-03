from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # Quick impossibility check
        if not set(s2).issubset(set(s1)):
            return 0

        len1, len2 = len(s1), len(s2)
        s1_count = s2_count = 0
        ptr = 0                     # current index in s2
        state = {0: (0, 0)}         # ptr -> (s1_count, s2_count) before any s1

        while s1_count < n1:
            # Process one full s1 string
            for ch in s1:
                if ch == s2[ptr]:
                    ptr += 1
                    if ptr == len2:
                        ptr = 0
                        s2_count += 1
            s1_count += 1

            # Check for a cycle
            if ptr in state:
                prev_s1, prev_s2 = state[ptr]
                cycle_s1 = s1_count - prev_s1
                cycle_s2 = s2_count - prev_s2

                # How many whole cycles fit in the remaining s1 repetitions
                remaining_s1 = n1 - s1_count
                cycles = remaining_s1 // cycle_s1
                s2_count += cycles * cycle_s2
                s1_count += cycles * cycle_s1

                # Process the leftover s1 repetitions (less than one cycle)
                for _ in range(n1 - s1_count):
                    for ch in s1:
                        if ch == s2[ptr]:
                            ptr += 1
                            if ptr == len2:
                                ptr = 0
                                s2_count += 1
                    s1_count += 1
                break
            else:
                state[ptr] = (s1_count, s2_count)

        return s2_count // n2