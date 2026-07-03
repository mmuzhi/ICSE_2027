from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If s2 has characters not in s1, it's impossible
        if not set(s2).issubset(set(s1)):
            return 0

        # Remove characters from s1 that are not in s2 (optimization)
        s1 = ''.join(char for char in s1 if char in set(s2))

        rec = [0]  # rec[i] = number of s1 copies used to match i full s2 strings
        track = defaultdict(int)  # maps state (position in s1) to index in rec
        ct = 0  # number of complete s1 copies consumed
        start = 0  # next search position in current s1 copy

        while True:
            # Try to match one full s2
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(char)
                start = ptr + 1
            # After matching s2, record the number of s1 copies used
            rec.append(ct + 1)

            # Check if we have used enough s1 copies
            used = rec[-1]
            if used > n1:
                # Cannot include this last s2 match
                return (len(rec) - 2) // n2
            if used == n1:
                # Exactly used all copies, include this match
                return (len(rec) - 1) // n2

            # State for cycle detection: the position in s1 after the last character of s2
            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                # Cycle detected
                break

        # Cycle analysis
        cycle_start_idx = track[ptr]  # index in rec where the cycle starts
        prefix_matches = cycle_start_idx  # number of s2 matches before the cycle
        prefix_s1 = rec[cycle_start_idx]  # s1 copies used in prefix
        cycle_matches = len(rec) - 1 - cycle_start_idx  # matches in one cycle
        cycle_s1 = rec[-1] - prefix_s1  # s1 copies used in one cycle

        # s1 copies remaining after the prefix
        rest = n1 - prefix_s1

        # Full cycles we can fit
        full_cycles = rest // cycle_s1
        leftover = rest % cycle_s1

        # Count extra matches that can be obtained from leftover s1 copies
        extra = 0
        for i in range(cycle_start_idx + 1, len(rec)):
            if rec[i] - prefix_s1 <= leftover:
                extra += 1
            else:
                break

        total_matches = prefix_matches + full_cycles * cycle_matches + extra
        return total_matches // n2