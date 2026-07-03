import collections

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        indexes = collections.defaultdict(collections.deque)
        for index, char in enumerate(s):
            digit = int(char)
            indexes[digit].append(index)
        
        count_t = {}
        for char in t:
            digit = int(char)
            count_t[digit] = count_t.get(digit, 0) + 1
        
        for digit, cnt in count_t.items():
            if digit not in indexes or len(indexes[digit]) < cnt:
                return False
        
        unique_t_values = set(count_t.keys())
        
        for char in t:
            digit = int(char)
            for d in range(digit):
                if d in unique_t_values and d in indexes and indexes[d] and indexes[d][0] < indexes[digit][0]:
                    return False
            indexes[digit].popleft()
            if len(indexes[digit]) == 0:
                del indexes[digit]
        
        return True