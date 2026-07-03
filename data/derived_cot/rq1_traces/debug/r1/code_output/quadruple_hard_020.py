class BIT:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)

    def sum(self, i):
        ans = 0
        i += 1
        while i > 0:
            ans += self.tree[i]
            i -= i & -i
        return ans

    def update(self, i, value):
        i += 1
        while i <= self.n:
            self.tree[i] += value
            i += i & -i

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        from collections import defaultdict, deque
        from collections import Counter

        if Counter(s) != Counter(t):
            return False
        ind = defaultdict(deque)
        for idx, c in enumerate(t):
            ind[c].append(idx)
        a = []
        for c in s:
            a.append(ind[c].popleft())
        n = len(a)
        bt = BIT(n)
        pos_info = defaultdict(lambda: -1)
        for i in range(n):
            inv = bt.sum(n - 1) - bt.sum(a[i])
            bt.update(a[i], 1)
            current_digit = int(s[i])
            for dig in range(current_digit - 1, -1, -1):
                if pos_info[dig] >= (i - inv):
                    return False
            pos_info[current_digit] = i - inv
        return True