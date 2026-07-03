from collections import defaultdict, deque

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        idx = defaultdict(deque)
        for i, c in enumerate(s):
            idx[int(c)].append(i)
        
        last_index = -1
        for c in t:
            d = int(c)
            while idx[d] and idx[d][0] <= last_index:
                idx[d].popleft()
            if not idx[d]:
                return False
            last_index = idx[d].popleft()
        return True