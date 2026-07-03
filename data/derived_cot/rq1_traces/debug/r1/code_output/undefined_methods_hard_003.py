from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        max_len = 0
        for f in forbidden:
            max_len = max(max_len, len(f))
            reversed_f = f[::-1]
            node = trie
            for c in reversed_f:
                if c not in node:
                    node[c] = {}
                node = node[c]
            node['#'] = True  # Mark the end of a forbidden word
        
        left = 0
        res = 0
        for right in range(len(word)):
            current = trie
            # Check all possible substrings ending at 'right' with length up to max_len
            for i in range(right, max(right - max_len, left - 1), -1):
                char = word[i]
                if char not in current:
                    break
                current = current[char]
                if '#' in current:
                    # Update left to i + 1 to exclude the forbidden substring
                    left = max(left, i + 1)
            res = max(res, right - left + 1)
        return res