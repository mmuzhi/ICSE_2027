from typing import List
import collections
import math

class Solution:
    def hasGroupsSizeX(self, deck: List[int]) -> bool:
        n = len(deck)
        if n < 2:
            return False
        
        count = collections.Counter(deck)
        freqs = list(count.values())
        g = freqs[0]
        for i in range(1, len(freqs)):
            g = math.gcd(g, freqs[i])
            if g == 1:
                break
                
        return g >= 2