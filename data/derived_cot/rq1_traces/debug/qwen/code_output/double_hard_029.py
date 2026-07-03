from functools import lru_cache

class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        
        @lru_cache(maxsize=None)
        def rec(i, j):
            if i > n or j > m:
                if i > n and j > m:
                    return 0
                elif i > n:
                    return m - j
                else:
                    return n - i
            if i == n and j == m:
                return 0
            elif i == n:
                return m - j
            elif j == m:
                return n - i
            elif word1[i] == word2[j]:
                return rec(i+1, j+1)
            else:
                insert = 1 + rec(i, j+1)
                delete = 1 + rec(i+1, j)
                replace = 1 + rec(i+1, j+1)
                return min(insert, delete, replace)
        
        return rec(0, 0)