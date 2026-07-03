class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word or not forbidden:
            return 0
        
        trie = {}
        for f in forbidden:
            t = trie
            for c in f:
                if c not in t:
                    t[c] = {}
                t = t[c]
            t["end"] = True
        
        def isForbidden(s):
            n = len(s)
            for start in range(n):
                t = trie
                for c in s[start:]:
                    if c in t:
                        t = t[c]
                        if "end" in t:
                            return True
                    else:
                        break
            return False
        
        n = len(word)
        i = 0
        max_len = 0
        for j in range(n):
            while isForbidden(word[i:j+1]):
                i += 1
            max_len = max(max_len, j - i + 1)
        return max_len