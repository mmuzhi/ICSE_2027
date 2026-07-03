from collections import defaultdict, deque
from collections import Counter

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) != Counter(t):
            return False
        
        pos_in_s = defaultdict(deque)
        for idx, char in enumerate(s):
            pos_in_s[char].append(idx)
        
        last_index = -1
        for char in t:
            if not pos_in_s[char] or pos_in_s[char][0] > last_index:
                return False
            pos = pos_in_s[char].popleft()
            last_index = pos
        
        return True