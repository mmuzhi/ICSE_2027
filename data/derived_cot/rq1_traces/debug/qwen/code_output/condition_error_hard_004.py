import collections

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        indexes = collections.defaultdict(collections.deque)
        for index, character in enumerate(s):
            indexes[int(character)].append(index)
        
        for char in t:
            digit = int(char)
            if digit not in indexes:
                return False
            for d in range(digit):
                if d in indexes and indexes[d] and indexes[d][0] < indexes[digit][0]:
                    return False
            indexes[digit].popleft()
            if len(indexes[digit]) == 0:
                del indexes[digit]
        return True