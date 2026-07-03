from collections import defaultdict, deque

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        indexes = defaultdict(deque)
        for i, char in enumerate(s):
            indexes[int(char)].append(i)
        
        last_index = -1
        for char in t:
            digit = int(char)
            if digit not in indexes or not indexes[digit] or indexes[digit][0] <= last_index:
                return False
            pos = indexes[digit].popleft()
            last_index = pos
        return True