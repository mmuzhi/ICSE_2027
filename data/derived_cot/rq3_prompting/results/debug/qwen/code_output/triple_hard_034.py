from collections import defaultdict, deque
from typing import Counter

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
        if Counter(s) != Counter(t):
            return False
        ind = defaultdict(deque)
        for idx, char in enumerate(t):
            ind[char].append(idx)
        a = []
        for char in s:
            a.append(ind[char].popleft())
        for i in range(1, len(a)):
            if a[i] < a[i-1]:
                return False
        return True