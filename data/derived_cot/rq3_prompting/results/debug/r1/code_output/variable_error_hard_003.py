from itertools import chain
from functools import lru_cache
from typing import List

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = sorted(chain(cuts, [0, n]))

        @lru_cache(maxsize=None)
        def dfs(l: int, r: int) -> int:
            if l + 1 == r:
                return 0
            length = cuts[r] - cuts[l]
            best = min(dfs(l, i) + dfs(i, r) for i in range(l + 1, r))
            return best + length

        return dfs(0, len(cuts) - 1)