class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        # Check diagonal and symmetry and the condition that lcp[i][j] <= min(n-i, n-j)
        for i in range(n):
            if lcp[i][i] != n - i:
                return ''
            for j in range(i+1, n):
                if lcp[i][j] != lcp[j][i]:
                    return ''
                if lcp[i][j] > min(n-i, n-j):
                    return ''
        
        # Build pattern array for the first character of each substring
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
        
        if next_el_ind > 26:
            return ''
        
        # Build the string from the pattern array
        ans = [chr(ord('a') + pattern[i]) for i in range(n)]
        
        # Check the entire LCP matrix
        for i in range(n):
            for j in range(n):
                if i > j:
                    continue
                common_length = 0
                while common_length < lcp[i][j] and i + common_length < n and j + common_length < n:
                    if ans[i + common_length] != ans[j + common_length]:
                        break
                    common_length += 1
                if common_length < lcp[i][j]:
                    return ''
        
        return ''.join(ans)