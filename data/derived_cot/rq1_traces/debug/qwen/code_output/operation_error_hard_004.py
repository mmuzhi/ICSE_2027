import math
from typing import List
import bisect

class Solution:
    def maximumSumQueries(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums1)
        points = []
        for i in range(n):
            points.append((nums1[i], nums2[i]))
        points.sort(key=lambda x: x[0])
        
        all_bs = []
        for a_val, b_val in points:
            all_bs.append(b_val)
        for query in queries:
            x, y = query
            all_bs.append(y)
        all_bs.sort()
        size_b = len(all_bs)
        def discretize(val):
            return bisect.bisect_left(all_bs, val)
        
        size = 1
        while size < size_b:
            size *= 2
        seg = [-10**18] * (2 * size)
        
        def update(pos, value):
            pos += size
            seg[pos] = max(seg[pos], value)
            while pos > 1:
                pos //= 2
                seg[pos] = max(seg[2*pos], seg[2*pos+1])
                
        def query(l, r):
            if l > r:
                return -10**18
            l += size
            r += size
            res = -10**18
            while l <= r:
                if l % 2 == 1:
                    res = max(res, seg[l])
                    l += 1
                if r % 2 == 0:
                    res = max(res, seg[r])
                    r -= 1
                l //= 2
                r //= 2
            return res
        
        sorted_queries = []
        for idx, (x, y) in enumerate(queries):
            sorted_queries.append((x, y, idx))
        sorted_queries.sort(key=lambda x: x[0])
        
        j = 0
        ans = [-1] * len(queries)
        for x, y, idx in sorted_queries:
            while j < n and points[j][0] <= x:
                b_val = points[j][1]
                s_val = points[j][0] + points[j][1]
                b_idx = discretize(b_val)
                update(b_idx, s_val)
                j += 1
            y_disc = discretize(y)
            if y_disc >= size_b:
                ans[idx] = -1
            else:
                res_val = query(y_disc, size_b - 1)
                if res_val < 0:
                    ans[idx] = -1
                else:
                    ans[idx] = res_val
        return ans