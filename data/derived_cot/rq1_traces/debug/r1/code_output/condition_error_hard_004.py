from collections import defaultdict, deque

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        indexes = defaultdict(deque)
        for index, character in enumerate(s):
            indexes[int(character)].append(index)

        for character in t:
            c = int(character)
            if c not in indexes:
                return False
            for i in range(c):
                if indexes.get(i, deque()) and indexes[i][0] < indexes[c][0]:
                    return False
            indexes[c].popleft()
            if not indexes[c]:
                del indexes[c]
        
        return True