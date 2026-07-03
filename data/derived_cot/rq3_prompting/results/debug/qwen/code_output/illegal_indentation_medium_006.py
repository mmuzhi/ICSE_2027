from collections import Counter
from typing import List

class Solution:
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        w2 = Counter()
        for word in words2:
            c = Counter(word)
            for letter in c:
                if c[letter] > w2[letter]:
                    w2[letter] = c[letter]
        return [w1 for w1 in words1 if Counter(w1) >= w2]