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
            t = trie
            for i in range(min(len(s), 10)):
                c = s[i]
                if c not in t:
                    return False
                t = t[c]
                if "end" in t:
                    return i+1
            return False
        
        res = 0
        j = len(word)
        for i in range(len(word)-1, -1, -1):
            truc = isForbidden(word[i:j])
            if truc:
                j = i + truc - 1
            res = max(res, j - i)
        return res