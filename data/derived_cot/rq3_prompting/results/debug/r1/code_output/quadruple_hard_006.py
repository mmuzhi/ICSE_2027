from typing import List

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
        
        n = len(word)
        res = 0
        j = n  # exclusive right boundary
        for i in range(n-1, -1, -1):
            t = trie
            # traverse from i to j-1 to find any forbidden word starting at i
            for k in range(i, j):
                c = word[k]
                if c not in t:
                    break
                t = t[c]
                if "end" in t:
                    j = k
                    break
            res = max(res, j - i)
        return res