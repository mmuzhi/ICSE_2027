class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        rec, track = [0], {} 
        ct = start = 0

        if not set(s2).issubset(set(s1)): return 0

        s1 = ''.join(char for char in s1 if char in set(s2))
        n = len(s1)
        
        while True:
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    ptr = s1.find(char)
                start = ptr + 1
            rec.append(ct + 1)

            if rec[-1] > n1: return (len(rec)-2)//n2

            if start % n not in track: track[start % n] = len(rec)-1
            else: break
        
        ptr = start % n
        s1_before_cycle = rec[track[ptr]]
        s2_before_cycle = track[ptr]
        s1_in_cycle = ct + 1 - s1_before_cycle
        s2_in_cycle = len(rec) - 1 - s2_before_cycle
        rest = n1 - s1_before_cycle
        
        rem_s1 = rest % s1_in_cycle
        m_rem = 0
        for i in range(1, s2_in_cycle + 1):
            if rec[s2_before_cycle + i] - rec[s2_before_cycle] <= rem_s1:
                m_rem = i
            else:
                break
                
        s2_count = s2_before_cycle + (rest // s1_in_cycle) * s2_in_cycle + m_rem
        return s2_count // n2