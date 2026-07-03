from collections import defaultdict
from typing import List

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        N = len(points)
        if N <= 2:
            return N
        
        point_count = defaultdict(int)
        for point in points:
            point_count[tuple(point)] += 1
        
        if len(point_count) == 1:
            return N
        
        D = defaultdict(int)
        max_points = 0
        unique_points = list(point_count.keys())
        for i in range(len(unique_points)):
            x1, y1 = unique_points[i]
            count1 = point_count[unique_points[i]]
            current_max = 0
            slope_count = defaultdict(int)
            for j in range(len(unique_points)):
                if i == j:
                    continue
                x2, y2 = unique_points[j]
                count2 = point_count[unique_points[j]]
                if x1 == x2:
                    slope = ('inf', x1)
                elif y1 == y2:
                    slope = (0, y1)
                else:
                    dx = x2 - x1
                    dy = y2 - y1
                    gcd = self.gcd(dy, dx)
                    dy //= gcd
                    dx //= gcd
                    if dx < 0:
                        dy, dx = -dy, -dx
                    slope = (dy, dx)
                slope_count[slope] += count2
            if slope_count:
                current_max = count1 + max(slope_count.values())
            else:
                current_max = count1
            max_points = max(max_points, current_max)
        return max_points
    
    def gcd(self, a, b):
        while b:
            a, b = b, a % b
        return a