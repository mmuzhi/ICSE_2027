from collections import deque

class Solution:
    def sequentialDigits(self, low, high):
        out = []
        queue = deque(range(1, 10))
        while queue:
            elem = queue.popleft()
            if low <= elem <= high:
                out.append(elem)
            last = elem % 10
            if last < 9:
                new_num = elem * 10 + (last + 1)
                queue.append(new_num)
        return out