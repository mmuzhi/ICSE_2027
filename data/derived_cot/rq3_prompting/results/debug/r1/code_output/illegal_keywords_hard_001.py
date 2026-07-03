from collections import Counter, defaultdict, deque

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        if Counter(s) != Counter(t):
            return False
        pos = defaultdict(deque)
        for i, ch in enumerate(t):
            pos[ch].append(i)
        for ch in s:
            p = pos[ch].popleft()
            for d in range(int(ch) + 1, 10):
                d_str = str(d)
                if pos[d_str] and pos[d_str][0] < p:
                    return False
        return True