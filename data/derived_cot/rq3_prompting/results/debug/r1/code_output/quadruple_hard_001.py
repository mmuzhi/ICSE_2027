class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If any character of s2 is missing from s1, impossible
        if not set(s2).issubset(set(s1)):
            return 0

        s1_len = len(s1)
        s2_len = len(s2)

        # repeat_count[i] = number of s2 repeats completed after i full s1 strings
        # next_index[i]   = index in s2 at the end of processing i full s1 strings
        repeat_count = [0] * (n1 + 1)
        next_index = [0] * (n1 + 1)

        index = 0
        count = 0

        for i in range(1, n1 + 1):
            for ch in s1:
                if ch == s2[index]:
                    index += 1
                    if index == s2_len:
                        count += 1
                        index = 0

            repeat_count[i] = count
            next_index[i] = index

            # Try to detect a cycle: same state (index) appears again
            for j in range(i - 1, -1, -1):
                if next_index[j] == index:
                    # Cycle from j+1 to i
                    prefix_count = repeat_count[j]
                    cycle_count = count - prefix_count
                    prefix_len = j                # number of s1 strings before cycle
                    cycle_len = i - j             # number of s1 strings in one cycle
                    remaining = n1 - prefix_len
                    cycles = remaining // cycle_len
                    remainder = remaining % cycle_len

                    total = prefix_count + cycles * cycle_count
                    total += repeat_count[prefix_len + remainder] - prefix_count

                    return total // n2

        # No cycle found, just return the total number of s2 repeats divided by n2
        return repeat_count[n1] // n2