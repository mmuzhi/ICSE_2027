from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        max_len = 0
        for f in forbidden:
            max_len = max(max_len, len(f))
            t = trie
            for c in f:
                if c not in t:
                    t[c] = {}
                t = t[c]
            t["end"] = True
        
        res = 0
        j = len(word)  # j is the end of the valid substring (exclusive)
        for i in range(len(word) - 1, -1, -1):
            current_j = j
            t = trie
            for k in range(i, min(i + max_len, len(word))):
                c = word[k]
                if c not in t:
                    break
                t = t[c]
                if "end" in t:
                    # Update current_j to the minimum possible end
                    current_j = min(current_j, i + (k - i + 1))
            j = current_j
            res = max(res, j - i)
        return res