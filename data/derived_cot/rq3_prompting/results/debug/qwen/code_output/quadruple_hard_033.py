from collections import Counter, defaultdict, deque

class BIT:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (self.n + 1)
    
    def update(self, i, value):
        index = i + 1
        while index <= self.n:
            self.tree[index] += value
            index -= index & -index

    def sum(self, i):
        s = 0
        index = i + 1
        while index:
            s += self.tree[index]
            index -= index & -index
        return s

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
        if n == 0:
            return True
        
        bt = BIT(n)
        ind_dict = defaultdict(lambda: -1)
        
        for i in range(n):
            inv = bt.sum(n) - bt.sum(a[i])
            bt.update(a[i], 1)
            for dig in range(int(s[i]) - 1, -1, -1):
                if ind_dict[dig] >= i - inv:
                    return False
            ind_dict[int(s[i])] = i - inv
        
        return True