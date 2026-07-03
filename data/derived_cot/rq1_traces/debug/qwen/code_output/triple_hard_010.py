class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        s1 = ''.join(char for char in s1 if char in set(s2))
        if not s1:
            return 0
        
        rec = [0]
        track = {}
        total_length = 0
        start = 0
        count = 0
        ptr2 = 0
        
        while total_length < n1 * len(s1):
            for char in s2:
                pos = s1.find(char, start)
                if pos == -1:
                    total_length += len(s1)
                    if total_length >= n1 * len(s1):
                        break
                    start = 0
                    pos = s1.find(char)
                    if pos == -1:
                        return 0
                else:
                    start = pos + 1
                if start >= len(s1):
                    start = 0
            else:
                count += 1
                rec.append(total_length)
                if rec[-1] >= n1:
                    return (len(rec) - 2) // n2
                if start not in track:
                    track[start] = len(rec) - 1
                else:
                    break
        
        if not track:
            return count // n2
        
        cycleStart = rec[track[start]]
        cycle1 = count - cycleStart
        cycle2 = len(rec) - 1 - track[start]
        rest = n1 - cycleStart
        rem = cycleStart + (rest // cycle1) * cycle1
        
        while ptr2 < len(rec) and rec[ptr2] <= rem:
            ptr2 += 1
        
        return (cycle2 * (rest // cycle1) + ptr2 - 1) // n2