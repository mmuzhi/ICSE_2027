class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if n1 == 0:
            return 0
            
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
                start = ptr + 1
                
            rec.append(ct + 1)

            if rec[-1] > n1: 
                return (len(rec) - 2) // n2

            if start not in track: 
                track[start] = len(rec) - 1
            else: 
                break
        
        cycleStart_idx = track[start]
        cycle1 = rec[-1] - rec[cycleStart_idx]
        cycle2 = len(rec) - 1 - cycleStart_idx
        
        remaining_s1 = (n1 - rec[cycleStart_idx]) % cycle1
        num_cycles = (n1 - rec[cycleStart_idx]) // cycle1
        
        k = 0
        while k < cycle2 and rec[cycleStart_idx + k + 1] - rec[cycleStart_idx] <= remaining_s1:
            k += 1
            
        total_s2 = cycleStart_idx + num_cycles * cycle2 + k
        return total_s2 // n2