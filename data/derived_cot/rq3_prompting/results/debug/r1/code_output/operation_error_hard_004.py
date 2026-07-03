import math
from typing import List

class Solution:
    def maximumSumQueries(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        # Coordinate compression of all nums2 values and query y values
        values = set(nums2)
        for _, y in queries:
            values.add(y)
        # Sort descending so that larger nums2 get smaller indices (suffix query)
        vals = sorted(values, reverse=True)
        comp = {v: i for i, v in enumerate(vals)}
        n_vals = len(vals)

        # Segment tree for range maximum (initialized to -1)
        size = 1
        while size < n_vals:
            size <<= 1
        seg = [-1] * (2 * size)

        def update(pos, val):
            i = pos + size
            seg[i] = max(seg[i], val)
            i >>= 1
            while i:
                seg[i] = max(seg[2 * i], seg[2 * i + 1])
                i >>= 1

        def query_range(l, r):
            if l > r:
                return -1
            l += size
            r += size
            res = -1
            while l <= r:
                if l & 1:
                    res = max(res, seg[l])
                    l += 1
                if not (r & 1):
                    res = max(res, seg[r])
                    r -= 1
                l >>= 1
                r >>= 1
            return res

        # Build list of (nums1, nums2, sum) and sort by nums1 descending
        pairs = [(nums1[i], nums2[i], nums1[i] + nums2[i]) for i in range(len(nums1))]
        pairs.sort(key=lambda x: -x[0])

        # Sort queries by x descending, keep original index
        qs = [(queries[i][0], queries[i][1], i) for i in range(len(queries))]
        qs.sort(key=lambda x: -x[0])

        res = [0] * len(queries)
        p_idx = 0

        for x, y, idx in qs:
            # Insert all pairs with nums1 >= x
            while p_idx < len(pairs) and pairs[p_idx][0] >= x:
                n2 = pairs[p_idx][1]
                s = pairs[p_idx][2]
                update(comp[n2], s)
                p_idx += 1

            # Binary search on `vals` (descending) to find the rightmost index with value >= y
            low, high = 0, n_vals - 1
            r = -1
            while low <= high:
                mid = (low + high) // 2
                if vals[mid] >= y:
                    r = mid
                    low = mid + 1
                else:
                    high = mid - 1

            if r >= 0:
                ans = query_range(0, r)
                res[idx] = ans if ans != -1 else -1
            else:
                res[idx] = -1

        return res