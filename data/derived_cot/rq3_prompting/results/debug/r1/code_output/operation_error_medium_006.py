from collections import Counter
from functools import reduce
import operator
from typing import List

class Solution:
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        # Combine all character frequency requirements from words2 by taking the maximum count per character
        w2 = reduce(operator.or_, map(Counter, words2), Counter())
        # Return words from words1 that satisfy all requirements
        return [w1 for w1 in words1 if Counter(w1) >= w2]