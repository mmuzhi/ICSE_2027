class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If any character of s2 is missing from s1, impossible
        if not set(s2).issubset(set(s1)):
            return 0

        # Keep only characters from s1 that appear in s2 (optimization)
        s1 = ''.join(c for c in s1 if c in set(s2))

        # State after processing each copy of s1
        index = 0           # current index in s2
        count_s2 = 0        # number of complete s2 matched so far
        seen = {}           # index_in_s2 -> (s1_copies_used, s2_matched)

        s1_copies = 0
        while s1_copies < n1:
            # Process one whole s1
            for c in s1:
                if c == s2[index]:
                    index += 1
                    if index == len(s2):
                        index = 0
                        count_s2 += 1
            s1_copies += 1

            # Check for a cycle in the state (only the index matters)
            if index in seen:
                prev_copies, prev_s2 = seen[index]
                cycle_copies = s1_copies - prev_copies
                cycle_s2 = count_s2 - prev_s2
                remaining = n1 - s1_copies
                full_cycles = remaining // cycle_copies
                count_s2 += full_cycles * cycle_s2
                s1_copies += full_cycles * cycle_copies
                break
            else:
                seen[index] = (s1_copies, count_s2)

        # Process any remaining s1 copies after the cycle
        while s1_copies < n1:
            for c in s1:
                if c == s2[index]:
                    index += 1
                    if index == len(s2):
                        index = 0
                        count_s2 += 1
            s1_copies += 1

        # Each complete s2 consists of n2 repetitions of s2
        return count_s2 // n2