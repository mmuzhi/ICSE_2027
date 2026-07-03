class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word:
            return 0
        
        forbidden_set = set()
        for f in forbidden:
            for i in range(len(f)):
                for j in range(i + 1, len(f) + 1):
                    forbidden_set.add(f[i:j])
        
        n = len(word)
        max_len = 0
        for i in range(n):
            for j in range(i, n):
                found = False
                for k in range(i, j + 1):
                    for l in range(k, j + 1):
                        if word[k:l] in forbidden_set:
                            found = True
                            break
                    if found:
                        break
                if not found:
                    max_len = max(max_len, j - i + 1)
        return max_len