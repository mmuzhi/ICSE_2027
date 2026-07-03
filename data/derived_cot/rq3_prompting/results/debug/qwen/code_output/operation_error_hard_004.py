import math
from typing import List
import bisect

class Solution:
    def maximumSumQueries(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        def buildSparseTable(arr, n):
            k = math.floor(math.log2(n)) + 1 if n > 0 else 0
            if n == 0:
                return None
            st = [[0] * n for _ in range(k)]
            for i in range(n):
                st[0][i] = arr[i]
            j = 1
            while (1 << j) <= n:
                i = 0
                while i + (1 << j) - 1 < n:
                    st[j][i] = max(st[j-1][i], st[j-1][i + (1 << (j-1))])
                    i += 1
                j += 1
            return st
        
        def getMax(st, n, l, r):
            if l > r:
                return 0
            length = r - l + 1
            k = math.floor(math.log2(length))
            return max(st[k][l], st[k][r - (1 << k) + 1])
        
        n = len(nums1)
        a = sorted([[nums1[i], nums2[i]] for i in range(n)])
        max_y = [0] * n
        for i in range(n):
            max_y[i] = a[i][1]
        for i in range(n-2, -1, -1):
            max_y[i] = max(max_y[i], max_y[i+1])
        _sum = [v[0] + v[1] for v in a]
        st_max_sum = buildSparseTable(_sum, n) if n > 0 else None
        res = []
        for x, y in queries:
            i = bisect.bisect_left(a, [x, -10**9])
            if i == n or (n > 0 and max_y[i] < y):
                res.append(-1)
                continue
            left, right = i, n-1
            while left < right:
                mid = (left + right + 1) // 2
                if max_y[mid] >= y:
                    left = mid
                else:
                    right = mid - 1
            j = left
            if n > 0:
                ans = getMax(st_max_sum, n, i, j)
                res.append(ans)
            else:
                res.append(-1)
        return res