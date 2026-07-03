from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        max_forbidden_len = 0
        for f in forbidden:
            max_forbidden_len = max(max_forbidden_len, len(f))
            node = trie
            for c in f:
                if c not in node:
                    node[c] = {}
                node = node[c]
            node['#'] = True  # Mark the end of a forbidden word
        
        left = 0
        max_len = 0
        for right in range(len(word)):
            current = trie
            # Check all possible substrings ending at 'right' with length up to max_forbidden_len
            for k in range(right, max(right - max_forbidden_len, left - 1), -1):
                c = word[k]
                if c not in current:
                    break
                current = current[c]
                if '#' in current:
                    left = max(left, k + 1)
            max_len = max(max_len, right - left + 1)
        return max_len