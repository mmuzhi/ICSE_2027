class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If any character of s2 is missing from s1, s2 cannot be a subsequence
        if not set(s2).issubset(set(s1)):
            return 0

        # Keep only characters that appear in s2 – speeds up scanning
        s1 = ''.join(ch for ch in s1 if ch in set(s2))
        s1_len, s2_len = len(s1), len(s2)

        # Precompute for each starting position in s1:
        #   next_idx[i] : index in s1 after matching one full s2
        #   rep_cnt[i]  : number of full s1 repetitions consumed
        next_idx = [0] * s1_len
        rep_cnt = [0] * s1_len
        for i in range(s1_len):
            cnt = 0
            idx = i
            for ch in s2:
                while s1[idx] != ch:
                    idx += 1
                    if idx == s1_len:
                        idx = 0
                        cnt += 1
                idx += 1
                if idx == s1_len:
                    idx = 0
                    cnt += 1
            next_idx[i] = idx
            rep_cnt[i] = cnt

        # Simulate the matching process over n1 repetitions of s1
        total_rep = 0        # how many s1 repetitions have been consumed
        total_match = 0      # how many full s2 strings have been matched
        ptr = 0
        seen = {}            # state -> (total_rep, total_match) for cycle detection

        while total_rep < n1:
            if ptr in seen:
                # Cycle detected
                prev_rep, prev_match = seen[ptr]
                cycle_rep = total_rep - prev_rep
                cycle_match = total_match - prev_match
                remaining = n1 - total_rep
                cycles = remaining // cycle_rep
                total_rep += cycles * cycle_rep
                total_match += cycles * cycle_match
                break
            seen[ptr] = (total_rep, total_match)
            total_rep += rep_cnt[ptr]
            total_match += 1
            ptr = next_idx[ptr]

        # Handle the remaining repetitions (after cycle or if no cycle)
        while total_rep < n1:
            total_rep += rep_cnt[ptr]
            total_match += 1
            ptr = next_idx[ptr]

        # The answer is the number of times we can repeat [s2,n2]
        return total_match // n2