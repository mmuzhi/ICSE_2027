class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        rec, track = [0], {}
        ct = start = 0

        if not set(s2).issubset(set(s1)):
            return 0

        s1 = ''.join(char for char in s1 if char in set(s2))
        
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

            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                break
        
        cycle_start = rec[track[ptr]]
        cycle1 = rec[-1] - cycle_start
        cycle2 = len(rec) - 1 - track[ptr]
        rest = n1 - cycle_start
        
        rem = cycle_start + (rest % cycle1)

        ptr2 = 0
        while ptr2 < len(rec) and rec[ptr2] <= rem:
            ptr2 += 1

        total_s2 = cycle2 * (rest // cycle1) + (ptr2 - 1 - track[ptr])
        return total_s2 // n2