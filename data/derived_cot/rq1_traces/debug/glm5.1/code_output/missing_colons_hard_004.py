from collections import Counter, defaultdict, deque

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) != Counter(t):
            return False
        ind = defaultdict(deque)
        for id, i in enumerate(t):
            ind[i].append(id)
        a = []
        for i in s:
            a.append(ind[i].popleft())
        n = len(a)
        ind = defaultdict(lambda: -1)
        for i in range(n):
            for dig in range(int(s[i]) - 1, -1, -1):
                if ind[dig] > a[i]:
                    return False
            ind[int(s[i])] = a[i]
        return True