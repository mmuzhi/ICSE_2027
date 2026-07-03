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
            for c in s:
                if c not in t:
                    t = trie
                else:
                    t = t[c]
                if "end" in t:
                    return True
            return False
        
        res = 0
        j = len(word)
        for i in range(len(word) - 1, -1, -1):
            if isForbidden(word[i:j]):
                j = i
            else:
                res = max(res, j - i)
        return res