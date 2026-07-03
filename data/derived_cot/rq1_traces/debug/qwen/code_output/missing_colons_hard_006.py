from collections import deque

class Solution:
    def kSimilarity(self, s1: str, s2: str) -> int:
        if s1 == s2:
            return 0
        
        dq = deque()
        seen = set()
        seen.add(s1)
        dq.append(s1)
        ans = 0
        
        while dq:
            size = len(dq)
            for _ in range(size):
                current = dq.popleft()
                if current == s2:
                    return ans
                
                n = len(current)
                for i in range(n - 1):
                    lst = list(current)
                    lst[i], lst[i + 1] = lst[i + 1], lst[i]
                    new_str = ''.join(lst)
                    if new_str not in seen:
                        seen.add(new_str)
                        dq.append(new_str)
            ans += 1
        
        return -1