import collections

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        indexes = collections.defaultdict(collections.deque)
        for index, char in enumerate(s):
            num = int(char)
            indexes[num].append(index)
        
        last_index = -1
        for char in t:
            d = int(char)
            found = False
            for digit in range(d, 10):
                if digit in indexes and indexes[digit] and indexes[digit][0] > last_index:
                    pos = indexes[digit].popleft()
                    last_index = pos
                    if not indexes[digit]:
                        del indexes[digit]
                    found = True
                    break
            if not found:
                return False
        return True