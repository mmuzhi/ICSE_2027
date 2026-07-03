class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0

        seen = {}
        s1_count = 0
        s2_count = 0
        j = 0

        while s1_count < n1:
            for ch in s1:
                if ch == s2[j]:
                    j += 1
                    if j == len(s2):
                        s2_count += 1
                        j = 0
            s1_count += 1

            if j in seen:
                prev_s1, prev_s2 = seen[j]
                cycle_s1 = s1_count - prev_s1
                cycle_s2 = s2_count - prev_s2
                remaining = n1 - s1_count
                cycles = remaining // cycle_s1
                s1_count += cycles * cycle_s1
                s2_count += cycles * cycle_s2
                break
            else:
                seen[j] = (s1_count, s2_count)

        while s1_count < n1:
            for ch in s1:
                if ch == s2[j]:
                    j += 1
                    if j == len(s2):
                        s2_count += 1
                        j = 0
            s1_count += 1

        return s2_count // n2