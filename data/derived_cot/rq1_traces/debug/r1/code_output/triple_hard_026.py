from typing import List

class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        if n == 0:
            return ''

        # Validate symmetry and diagonal elements
        for i in range(n):
            if lcp[i][i] != n - i:
                return ''
            for j in range(i + 1, n):
                if lcp[i][j] != lcp[j][i] or lcp[i][j] > n - j:
                    return ''

        # Build the pattern
        pattern = [None] * n
        next_char = 0
        for i in range(n):
            if pattern[i] is not None:
                continue
            if next_char >= 26:
                return ''
            pattern[i] = next_char
            for j in range(i + 1, n):
                if lcp[i][j] > 0:
                    if pattern[j] is not None and pattern[j] != pattern[i]:
                        return ''
                    pattern[j] = pattern[i]
            next_char += 1

        # Generate LCP from pattern and compare
        computed_lcp = [[0] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            for j in range(n-1, -1, -1):
                if i == j:
                    computed_lcp[i][j] = n - i
                else:
                    if pattern[i] == pattern[j]:
                        if i + 1 < n and j + 1 < n:
                            computed_lcp[i][j] = computed_lcp[i+1][j+1] + 1
                        else:
                            computed_lcp[i][j] = 1
                    else:
                        computed_lcp[i][j] = 0

        for i in range(n):
            for j in range(n):
                if computed_lcp[i][j] != lcp[i][j]:
                    return ''

        # Check character count
        if max(pattern) >= 26:
            return ''

        return ''.join(chr(ord('a') + c) for c in pattern)