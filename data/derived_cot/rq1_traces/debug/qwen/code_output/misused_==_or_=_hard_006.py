import math
from typing import List

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        n = len(points)
        if n <= 1:
            return n
        
        seen = set()
        max_count = 0
        
        for i in range(n):
            x1, y1 = points[i]
            for j in range(i+1, n):
                x2, y2 = points[j]
                if points[i] == points[j]:
                    continue
                
                if x1 == x2:
                    A = 1
                    B = 0
                    C = -x1
                else:
                    A = y2 - y1
                    B = x1 - x2
                    C = x2 * y1 - x1 * y2
                
                nums = []
                if A != 0:
                    nums.append(abs(A))
                if B != 0:
                    nums.append(abs(B))
                if C != 0:
                    nums.append(abs(C))
                
                if not nums:
                    g = 1
                else:
                    g = nums[0]
                    for num in nums[1:]:
                        g = math.gcd(g, num)
                
                A_norm = A // g
                B_norm = B // g
                C_norm = C // g
                
                if A_norm < 0:
                    A_norm, B_norm, C_norm = -A_norm, -B_norm, -C_norm
                elif A_norm == 0:
                    if B_norm < 0:
                        B_norm, C_norm = -B_norm, -C_norm
                    elif B_norm == 0:
                        if C_norm < 0:
                            C_norm = -C_norm
                key = (A_norm, B_norm, C_norm)
                
                if key in seen:
                    continue
                seen.add(key)
                
                count = 0
                for k in range(n):
                    x, y = points[k]
                    if A_norm * x + B_norm * y + C_norm == 0:
                        count += 1
                if count > max_count:
                    max_count = count
        
        return max_count