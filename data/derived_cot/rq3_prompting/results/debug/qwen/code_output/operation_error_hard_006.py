from collections import defaultdict, deque
from collections import Counter

class BIT():
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)

    def sum(self, i):
        ans = 0
        i += 1
        while i > 0:
            ans += self.tree[i]
            i -= (i & (-i))
        return ans

    def update(self, i, value):
        i += 1
        while i <= self.n:
            self.tree[i] += value
            i -= (i & (-i))

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) & Counter(t) != Counter(s):
            return False
        ind = defaultdict(deque)
        for idx, char in enumerate(t):
            ind[char].append(idx)
        a = []
        for char in s:
            a.append(ind[char].popleft())
        n = len(a)
        bt = BIT(n + 1)
        last_occurrence = defaultdict(lambda: -1)
        for i in range(n):
            inv = bt.sum(n) - bt.sum(a[i])
            bt.update(a[i], 1)
            for dig in range(int(s[i]) - 1, -1, -1):
                if last_occurrence[dig] >= i - inv:
                    return False
            last_occurrence[int(s[i])] = i - inv
        return True