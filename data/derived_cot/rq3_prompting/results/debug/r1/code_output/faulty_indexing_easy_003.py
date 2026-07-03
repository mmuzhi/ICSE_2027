from typing import List
import collections
import math

class Solution:
    def hasGroupsSizeX(self, deck: List[int]) -> bool:
        count = collections.Counter(deck)
        vals = list(count.values())  # list of frequencies
        g = math.gcd(*vals)          # greatest common divisor of all frequencies
        return g >= 2