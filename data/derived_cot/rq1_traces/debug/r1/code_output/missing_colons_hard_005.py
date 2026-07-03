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
        
        def is_forbidden(s):
            t = trie
            for c in s:
                if c not in t:
                    return False
                t = t[c]
            return "end" in t
        
        left = 0
        max_length = 0
        for right in range(len(word)):
            # Check all possible substrings ending at 'right' with length up to max_len
            for k in range(0, max_len):
                start = right - k
                if start < 0:
                    break
                substring = word[start:right+1]
                if is_forbidden(substring):
                    left = max(left, start + 1)
            current_length = right - left + 1
            if current_length > max_length:
                max_length = current_length
        return max_length