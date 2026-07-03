class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word:
            return 0
        
        trie = {}
        for f in forbidden:
            t = trie
            for c in f:
                if c not in t:
                    t[c] = {}
                t = t[c]
            t["end"] = True
        
        def containsForbidden(s):
            n = len(s)
            if n == 0:
                return False
            for start in range(n):
                t = trie
                matched = 0
                for i in range(start, n):
                    c = s[i]
                    if c not in t:
                        break
                    t = t[c]
                    matched += 1
                    if "end" in t:
                        return True
            return False
        
        n = len(word)
        max_len = 0
        for i in range(n):
            j = i
            while j < n:
                if not containsForbidden(word[i:j+1]):
                    j += 1
                else:
                    break
            max_len = max(max_len, j - i)
        return max_len