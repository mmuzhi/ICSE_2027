from typing import List

class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        # Validate symmetry and lcp[i][j] <= possible maximum
        for i in range(n):
            for j in range(i + 1, n):
                if lcp[i][j] != lcp[j][i]:
                    return ''
                if lcp[i][j] > n - j:
                    return ''
        # Validate diagonal elements
        for i in range(n):
            if lcp[i][i] != n - i:
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
            next_char += 1
            for j in range(i + 1, n):
                if lcp[i][j] > 0:
                    if pattern[j] is not None and pattern[j] != pattern[i]:
                        return ''
                    pattern[j] = pattern[i]
        
        # Check if the generated pattern's LCP matches the input
        # Compute pattern_lcp
        pattern_lcp = [[0] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            for j in range(n-1, -1, -1):
                if pattern[i] == pattern[j]:
                    if i + 1 < n and j + 1 < n:
                        pattern_lcp[i][j] = pattern_lcp[i+1][j+1] + 1
                    else:
                        pattern_lcp[i][j] = 1
                else:
                    pattern_lcp[i][j] = 0
        
        # Compare with input lcp
        for i in range(n):
            for j in range(n):
                if lcp[i][j] != pattern_lcp[i][j]:
                    return ''
        
        # Check if the number of distinct characters exceeds 26
        if max(pattern) >= 26:
            return ''
        
        # Convert to string
        return ''.join(chr(ord('a') + c) for c in pattern)