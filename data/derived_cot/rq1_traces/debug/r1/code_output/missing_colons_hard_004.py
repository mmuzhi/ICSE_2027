from collections import defaultdict, deque, Counter

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
        if Counter(s) != Counter(t):
            return False
        pos_map = defaultdict(deque)
        for idx, char in enumerate(t):
            pos_map[char].append(idx)
        a = []
        for char in s:
            if not pos_map[char]:
                return False
            current_pos = pos_map[char].popleft()
            current_digit = int(char)
            for d in range(current_digit - 1, -1, -1):
                if pos_map.get(str(d), deque()) and pos_map[str(d)][0] < current_pos:
                    return False
            a.append(current_pos)
        return True