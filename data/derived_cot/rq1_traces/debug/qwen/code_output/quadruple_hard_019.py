class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        total_length = n1 * len(s1)
        if total_length == 0:
            return 0
        
        count = 0
        j = 0
        for i in range(total_length):
            current_char = s1[i % len(s1)]
            if current_char == s2[j]:
                j += 1
                if j == len(s2):
                    count += 1
                    j = 0
        return count // n2