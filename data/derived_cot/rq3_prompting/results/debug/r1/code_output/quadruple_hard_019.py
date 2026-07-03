class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        len1, len2 = len(s1), len(s2)
        seen = {}  # pos in s2 -> (s1_count, s2_count)
        s1_count = 0
        s2_count = 0
        pos = 0  # index in s2
        while s1_count < n1:
            if pos in seen:
                prev_s1, prev_s2 = seen[pos]
                cycle_len = s1_count - prev_s1
                cycle_s2 = s2_count - prev_s2
                cycles = (n1 - prev_s1) // cycle_len
                s1_count = prev_s1 + cycles * cycle_len
                s2_count = prev_s2 + cycles * cycle_s2
                # Process remaining s1 scans one by one
                for _ in range(n1 - s1_count):
                    for ch in s1:
                        if ch == s2[pos]:
                            pos += 1
                            if pos == len2:
                                s2_count += 1
                                pos = 0
                    s1_count += 1
                break
            else:
                seen[pos] = (s1_count, s2_count)
                # Process one full s1
                for ch in s1:
                    if ch == s2[pos]:
                        pos += 1
                        if pos == len2:
                            s2_count += 1
                            pos = 0
                s1_count += 1
        return s2_count // n2