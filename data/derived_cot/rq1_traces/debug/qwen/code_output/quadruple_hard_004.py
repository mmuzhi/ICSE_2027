class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        
        # Check diagonal condition
        for i in range(n):
            if lcp[i][i] != n - i:
                return ''
        
        # Check symmetry and bounds for i < j
        for i in range(n):
            for j in range(i+1, n):
                if lcp[i][j] != lcp[j][i]:
                    return ''
                if lcp[i][j] > n - j:
                    return ''
        
        # Build the pattern array
        pattern = [None] * n
        next_el_ind = 0
        for i in range(n):
            if pattern[i] is not None:
                continue
            pattern[i] = next_el_ind
            next_el_ind += 1
            for j in range(i+1, n):
                if lcp[i][j] > 0:
                    if pattern[j] is not None and pattern[j] != pattern[i]:
                        return ''
                    pattern[j] = pattern[i]
        
        # Check converse condition
        for i in range(n):
            for j in range(n):
                if pattern[i] == pattern[j]:
                    if lcp[i][j] <= 0:
                        return ''
                else:
                    if lcp[i][j] > 0:
                        return ''
        
        # Build pattern_lcp matrix
        pattern_lcp = [[0]*n for _ in range(n)]
        for i in range(n-1, -1, -1):
            for j in range(n-1, -1, -1):
                if pattern[i] == pattern[j]:
                    if i+1 < n and j+1 < n:
                        pattern_lcp[i][j] = 1 + pattern_lcp[i+1][j+1]
                    else:
                        pattern_lcp[i][j] = 1
                else:
                    pattern_lcp[i][j] = 0
        
        # Compare pattern_lcp with lcp
        for i in range(n):
            for j in range(n):
                if pattern_lcp[i][j] != lcp[i][j]:
                    return ''
        
        # Check the number of distinct characters
        if next_el_ind > 26:
            return ''
        
        # Build the result string
        return ''.join(chr(ord('a') + x) for x in pattern)