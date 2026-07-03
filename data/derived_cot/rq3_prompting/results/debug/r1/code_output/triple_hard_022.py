from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        # If any character in s2 is missing from s1, impossible
        if not set(s2).issubset(set(s1)):
            return 0
        
        # Remove characters from s1 that are not in s2
        s1 = ''.join(c for c in s1 if c in set(s2))
        
        # rec[i] = number of s1 repetitions consumed to match i copies of s2
        # idx[i] = the starting index in s1 after matching i copies
        rec = [0]
        idx = [0]
        repeat_count = 0
        start = 0
        
        while True:
            # Match one s2
            for ch in s2:
                pos = s1.find(ch, start)
                if pos == -1:
                    repeat_count += 1
                    pos = s1.find(ch)
                start = pos + 1
            
            # Record after this match
            rec.append(repeat_count + 1)
            idx.append(start)
            
            # If we have consumed more than n1 s1, we can't complete this match
            if rec[-1] > n1:
                # The last complete match is the previous one
                return (len(rec) - 2) // n2
            
            # Check for a cycle
            for j in range(len(rec) - 1):
                if idx[j] == start:
                    # Cycle from j to len(rec)-1
                    prefix_s2 = j
                    cycle_s2 = len(rec) - 1 - j
                    cycle_s1 = rec[-1] - rec[j]
                    
                    # Number of full cycles after prefix
                    cycles = (n1 - rec[j]) // cycle_s1
                    total_s2 = prefix_s2 + cycles * cycle_s2
                    
                    # Remaining s1 repetitions
                    remaining_s1 = (n1 - rec[j]) % cycle_s1
                    
                    # Find extra s2 matches in remaining s1 using precomputed counts
                    extra = 0
                    for k in range(j + 1, len(rec)):
                        if rec[k] - rec[j] <= remaining_s1:
                            extra = k - j
                        else:
                            break
                    
                    total_s2 += extra
                    return total_s2 // n2