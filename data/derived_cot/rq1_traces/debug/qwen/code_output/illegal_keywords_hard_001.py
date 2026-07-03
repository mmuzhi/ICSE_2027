from collections import Counter, defaultdict, deque

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

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) != Counter(t):
            return False
        pos_dict = defaultdict(deque)
        for idx, char in enumerate(t):
            pos_dict[char].append(idx)
        a = []
        for char in s:
            a.append(pos_dict[char].popleft())
        n = len(a)
        bt = BIT(n)
        count = defaultdict(int)
        for i in range(n):
            inv = bt.sum(n) - bt.sum(a[i])
            bt.update(a[i], 1)
            current_digit = int(s[i])
            for dig in range(current_digit - 1, -1, -1):
                if count.get(str(dig), 0) >= i - inv:
                    return False
            count[s[i]] += 1
        return True