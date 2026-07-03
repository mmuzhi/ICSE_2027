from collections import Counter
import math

class Solution:
    def hasGroupsSizeX(self, deck: List[int]) -> bool:
        count = Counter(deck)
        val = count.values()
        if not val:
            return False
        m = math.gcd(*val)
        return m >= 2