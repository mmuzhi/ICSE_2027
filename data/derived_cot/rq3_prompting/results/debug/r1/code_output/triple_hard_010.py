from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        rec, track = [0], defaultdict(int)
        ct = start = ptr1 = ptr2 = 0

        if not set(s2).issubset(set(s1)):
            return 0

        # Remove characters from s1 that cannot appear in s2
        s1 = ''.join(ch for ch in s1 if ch in set(s2))

        while True:
            for ch in s2:
                ptr = s1.find(ch, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(ch)
                start = ptr + 1
            rec.append(ct + 1)

            # Exactly used all n1 repeats
            if rec[-1] == n1:
                return (len(rec) - 1) // n2
            # Exceeded n1 -> last complete match is the one before this
            if rec[-1] > n1:
                return (len(rec) - 2) // n2

            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                break

        # Cycle detected
        cycle_start = rec[track[ptr]]
        cycle1 = ct + 1 - cycle_start
        cycle2 = len(rec) - 1 - track[ptr]
        rest = n1 - cycle_start
        rem = cycle_start + rest % cycle1

        while rec[ptr2] <= rem:
            ptr2 += 1

        return (cycle2 * (rest // cycle1) + ptr2 - 1) // n2