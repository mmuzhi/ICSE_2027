class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        from functools import lru_cache
        n, m = len(word1), len(word2)
        
        @lru_cache(None)
        def rec(i, j):
            if i == n and j == m:
                return 0
            elif i == n:
                return m - j
            elif j == m:
                return n - i
            elif word1[i] == word2[j]:
                return rec(i + 1, j + 1)
            else:
                res = 1 + rec(i, j + 1)  # Insert
                res = min(res, 1 + rec(i + 1, j))  # Delete
                res = min(res, 1 + rec(i + 1, j + 1))  # Replace
                return res
        
        return rec(0, 0)