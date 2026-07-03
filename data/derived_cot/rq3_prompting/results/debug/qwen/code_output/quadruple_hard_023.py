class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
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
                for pos in range(start, n):
                    c = s[pos]
                    if c in t:
                        t = t[c]
                        if "end" in t:
                            return pos - start + 1
                    else:
                        break
            return 0
        
        res = 0
        j = len(word) + 1
        for i in range(len(word) - 1, -1, -1):
            truc = isForbidden(word[i:j])
            if truc:
                j = i + truc - 1
            res = max(res, j - i)
        return res