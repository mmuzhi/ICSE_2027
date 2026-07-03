from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        max_len = 0
        for f in forbidden:
            max_len = max(max_len, len(f))
            reversed_f = f[::-1]
            t = trie
            for c in reversed_f:
                if c not in t:
                    t[c] = {}
                t = t[c]
            t["end"] = True
        
        left = 0
        res = 0
        for right in range(len(word)):
            current = trie
            for k in range(max_len):
                pos = right - k
                if pos < 0:
                    break
                c = word[pos]
                if c not in current:
                    break
                current = current[c]
                if "end" in current:
                    left = max(left, pos + 1)
            res = max(res, right - left + 1)
        return res