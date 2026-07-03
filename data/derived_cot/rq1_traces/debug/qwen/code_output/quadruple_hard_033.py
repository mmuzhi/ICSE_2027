from collections import Counter, defaultdict, deque

class BIT:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
    
    def sum(self, i):
        ans = 0
        i += 1
        while i > 0:
            ans += self.tree[i]
            i -= (i & -i)
        return ans

    def update(self, i, value):
        i += 1
        while i <= self.n:
            self.tree[i] += value
            i -= (i & -i)

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) != Counter(t):
            return False
        
        char_to_positions = defaultdict(deque)
        for idx, char in enumerate(t):
            char_to_positions[char].append(idx)
        
        integer_to_position = {}
        for char, deq in char_to_positions.items():
            digit = int(char)
            if deq:
                integer_to_position[digit] = deq[0]
        
        n = len(s)
        bt = BIT(n)
        a = []
        for char in s:
            a.append(char_to_positions[char].popleft())
        
        s_int = [int(char) for char in s]
        
        for i in range(n):
            inv = bt.sum(n) - bt.sum(a[i])
            bt.update(a[i], 1)
            for dig in range(s_int[i] - 1, -1, -1):
                if dig not in integer_to_position:
                    continue
                if integer_to_position[dig] >= i - inv:
                    return False
        return True