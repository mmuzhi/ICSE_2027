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
        
        def isForbidden(s):
            t = trie
            for idx, c in enumerate(s):
                if c not in t:
                    return False
                t = t[c]
                if "end" in t:
                    return idx + 1
            return False
        
        n = len(word)
        j = n + 1
        res = 0
        for i in range(n - 1, -1, -1):
            truc = isForbidden(word[i:j])
            if truc:
                j = i + truc
            res = max(res, j - i)
        return res