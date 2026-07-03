from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return 0
        # Build the prefix array for s2
        pi = [0] * len(s2)
        j = 0
        for i in range(1, len(s2)):
            while j > 0 and s2[i] != s2[j]:
                j = pi[j-1]
            if s2[i] == s2[j]:
                j += 1
            else:
                j = 0
            pi[i] = j

        count = 0
        state = 0
        for _ in range(n1):
            for char in s1:
                while state > 0 and char != s2[state]:
                    state = pi[state-1]
                if char == s2[state]:
                    state += 1
                else:
                    state = 0
                if state == len(s2):
                    count += 1
                    state = 0
        return count