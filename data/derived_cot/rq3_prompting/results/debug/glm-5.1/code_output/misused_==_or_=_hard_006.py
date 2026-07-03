from collections import defaultdict
from math import gcd
from typing import List

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        N = len(points)
        if N <= 2:
            return N
        D = defaultdict(set)
        for i in range(N):
            x1, y1 = points[i]
            for j in range(i+1, N):
                x2, y2 = points[j]
                a = y2 - y1
                b = x1 - x2
                c = x2 * y1 - x1 * y2
                if a == 0 and b == 0:
                    continue
                g = gcd(gcd(abs(a), abs(b)), abs(c))
                a //= g
                b //= g
                c //= g
                if a < 0 or (a == 0 and b < 0):
                    a, b, c = -a, -b, -c
                D[(a, b, c)].add(i)
                D[(a, b, c)].add(j)
        if not D:
            return N
        return max(len(s) for s in D.values())