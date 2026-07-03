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
            i += (i & (-i))

from collections import defaultdict, deque
from typing import Counter

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) != Counter(t):
            return False
        ind = defaultdict(deque)
        for idx, char in enumerate(t):
            ind[char].append(idx)
        a = []
        for char in s:
            a.append(ind[char].popleft())
        n = len(a)
        bt = BIT(n)
        used = [-1] * 10
        for i in range(n):
            pos = a[i]
            bt.update(pos, 1)
            for dig in range(int(s[i]) - 1, -1, -1):
                if used[dig] >= i - bt.sum(pos):
                    return False
            used[int(s[i])] = i - bt.sum(pos)
        return True