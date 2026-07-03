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
        
        def isForbidden(s: str):
            t = trie
            counter = 0
            for c in s:
                if c not in t:
                    return False
                t = t[c]
                counter += 1
                if "end" in t:
                    return counter
            return False
        
        res = 0
        j = len(word) + 1
        for i in range(len(word) - 1, -1, -1):
            length = isForbidden(word[i:j])
            if length:
                j = i + length - 1
            res = max(res, j - i)
        return res