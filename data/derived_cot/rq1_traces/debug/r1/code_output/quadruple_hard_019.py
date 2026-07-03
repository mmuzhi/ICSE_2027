class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        from collections import defaultdict

        rec = [0]  # rec[i] tracks the number of s1's used to form i s2's
        track = defaultdict(int)
        ct = 0  # Count of s1's used
        start = 0  # Start index in s1 for the next search

        # Check if all characters of s2 are present in s1
        if not set(s2).issubset(set(s1)):
            return 0

        # Optimize s1 by keeping only characters present in s2
        s2_chars = set(s2)
        s1 = ''.join([c for c in s1 if c in s2_chars])

        while True:
            # Form one s2
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1  # Use another s1
                    ptr = s1.find(char)
                    if ptr == -1:
                        return 0  # Shouldn't happen due to subset check
                start = ptr + 1  # Move start to next position

            # Record the total s1's used (ct + 1)
            rec.append(ct + 1)

            # Check if we've used up all available s1's
            if rec[-1] > n1:
                return (len(rec) - 2) // n2
            elif rec[-1] == n1:
                return (len(rec) - 1 - 1) // n2

            # Check for cycle using the end position of the last character in s2
            last_ptr = ptr
            if last_ptr in track:
                break
            track[last_ptr] = len(rec) - 1  # Current s2 count

        # Calculate cycle parameters
        cycle_start_s2_count = track[last_ptr]
        cycle_s1_start = rec[cycle_start_s2_count]
        cycle_s1_length = rec[-1] - cycle_s1_start
        cycle_s2_length = len(rec) - 1 - cycle_start_s2_count

        # Remaining s1's after the cycle starts
        remaining_s1 = n1 - cycle_s1_start

        # Number of full cycles and remainder
        full_cycles = remaining_s1 // cycle_s1_length
        remainder_s1 = remaining_s1 % cycle_s1_length

        # Total s2's from full cycles
        total_s2 = full_cycles * cycle_s2_length

        # Add s2's from the remainder part
        remainder_total_s1 = cycle_s1_start + remainder_s1
        ptr2 = 0
        while ptr2 < len(rec) and rec[ptr2] <= remainder_total_s1:
            ptr2 += 1
        ptr2 -= 1  # Index of maximum rec[k] <= remainder_total_s1
        total_s2 += ptr2 - cycle_start_s2_count

        return total_s2 // n2