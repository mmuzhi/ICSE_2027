import sys
from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        s1 = ''.join(char for char in s1 if char in set(s2))
        len_s1 = len(s1)
        
        if len_s1 == 0:
            return 0
        
        rec, track = [0], defaultdict(int) 
        ct = start = ptr = 0
        
        while True:
            for char in s2:
                ptr = s1.find(char, start)
                if ptr == -1:
                    ct += 1
                    if ct >= n1:
                        break
                    ptr = s1.find(char, 0)
                    start = 0
                else:
                    start = ptr + 1
            total_chars = ct * len_s1 + start
            rec.append(total_chars)
            
            if total_chars > n1 * len_s1:
                return (len(rec) - 2) // n2

            if ptr not in track:
                track[ptr] = len(rec) - 1
            else:
                break
        
        cycleStart = rec[track[ptr]]
        cycle1 = total_chars - cycleStart
        cycle2 = len(rec) - 1 - track[ptr]
        rest = n1 * len_s1 - cycleStart
        
        rem = cycleStart + rest % cycle1
        
        while rec[ptr] <= rem:
            ptr += 1
        
        return (cycle2 * (rest // cycle1) + ptr - 2) // n2