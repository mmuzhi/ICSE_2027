from collections import defaultdict

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
                if y1 == y2:
                    key = ('inf', y1)
                elif x1 == x2:
                    key = (x1, 'inf')
                else:
                    slope = (y2 - y1) / (x2 - x1)
                    intercept = y1 - slope * x1
                    key = (slope, intercept)
                D[key].add(tuple(points[i]))
                D[key].add(tuple(points[j]))
        
        return max(len(point_set) for point_set in D.values()) if D else 0