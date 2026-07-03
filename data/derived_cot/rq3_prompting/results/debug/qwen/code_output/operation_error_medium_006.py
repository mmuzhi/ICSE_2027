from collections import Counter

class Solution:
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        w2_max = {}
        for c in map(Counter, words2):
            for char, count_val in c.items():
                w2_max[char] = max(w2_max.get(char, 0), count_val)
        return [w1 for w1 in words1 if Counter(w1) >= w2_max]