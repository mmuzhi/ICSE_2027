class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return 0
        if not set(s2).issubset(set(s1)):
            return 0
        if n1 == 0:
            return 0
        
        s = s1 * n1
        count = 0
        j = 0
        
        for c in s:
            if j < len(s2) and c == s2[j]:
                j += 1
            else:
                if j > 0 and c == s2[0]:
                    j = 1
                else:
                    j = 0
            if j == len(s2):
                count += 1
                j = 0
        
        return count // n2