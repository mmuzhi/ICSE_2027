class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        
        from collections import defaultdict
        freq1 = defaultdict(int)
        for char in s1:
            freq1[char] += 1
        
        freq2 = defaultdict(int)
        for char in s2:
            freq2[char] += 1
        
        max_repetitions = float('inf')
        for char in set(s2):
            if freq2[char] == 0:
                continue
            max_for_char = (freq1[char] * n1) // freq2[char]
            if max_for_char < max_repetitions:
                max_repetitions = max_for_char
        
        return max_repetitions // n2