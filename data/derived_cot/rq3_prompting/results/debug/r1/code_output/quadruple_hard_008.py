class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If any character in s2 is not in s1, it's impossible to form s2
        if not set(s2).issubset(set(s1)):
            return 0

        # Keep only characters in s2 to speed up searching
        s1 = ''.join(ch for ch in s1 if ch in set(s2))

        ct = 0          # number of full s1 strings consumed
        start = 0       # current search start index in s1
        rec = [0]       # rec[i] = total s1 strings used after i s2 matches (0‑based)
        track = {}      # map from (start index) -> index in rec

        while True:
            # Try to match one occurrence of s2
            for char in s2:
                pos = s1.find(char, start)
                if pos == -1:
                    ct += 1
                    # Ran out of s1 repetitions before completing this s2
                    if ct >= n1:
                        return (len(rec) - 1) // n2
                    pos = s1.find(char)
                start = pos + 1

            # Successfully matched one s2, record the number of s1 strings used
            rec.append(ct + 1)

            # Check if we have already used all n1 s1 strings
            if rec[-1] >= n1:
                if rec[-1] > n1:
                    # Last match overshoots – use the number of matches before it
                    return (len(rec) - 2) // n2
                else:
                    # Exactly exhausted n1 – include this match
                    return (len(rec) - 1) // n2

            # Cycle detection using the start index for the next s2 match
            if start in track:
                break
            track[start] = len(rec) - 1

        # Cycle found – compute the total matches using the cycle
        idx_cycle = track[start]               # index in rec where the cycle begins
        s1_cycle = rec[idx_cycle]              # s1 strings used at cycle start
        s1_per_cycle = (ct + 1) - s1_cycle     # s1 strings in one full cycle
        s2_per_cycle = len(rec) - 1 - idx_cycle   # s2 matches in one full cycle

        rest = n1 - s1_cycle                   # s1 strings available after precycle
        full_cycles = rest // s1_per_cycle
        remainder = rest % s1_per_cycle

        # Count how many s2 matches fit in the remainder (inside the cycle)
        i = idx_cycle + 1                     # first match inside the cycle
        while i < len(rec) and (rec[i] - s1_cycle) <= remainder:
            i += 1
        extra = i - (idx_cycle + 1)

        total_s2 = idx_cycle + full_cycles * s2_per_cycle + extra
        return total_s2 // n2