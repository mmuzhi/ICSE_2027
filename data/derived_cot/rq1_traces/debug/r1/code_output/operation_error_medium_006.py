from collections import Counter
from typing import List

class Solution:
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        max_counts = Counter()
        for word in words2:
            cnt = Counter(word)
            for char, count in cnt.items():
                max_counts[char] = max(max_counts[char], count)
        return [w1 for w1 in words1 if Counter(w1) >= max_counts]