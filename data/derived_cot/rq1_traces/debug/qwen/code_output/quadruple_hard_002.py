class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return 0
        T = s1 * n1
        count = 0
        len_s2 = len(s2)
        for i in range(len(T) - len_s2 + 1):
            if T[i:i+len_s2] == s2:
                count += 1
        return count // n2