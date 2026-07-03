from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        # Build trie of forbidden words
        trie = {}
        max_len = 0
        for f in forbidden:
            max_len = max(max_len, len(f))
            node = trie
            for ch in f:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node['#'] = True  # mark end of word

        n = len(word)
        left = 0
        ans = 0
        for right in range(n):
            # Check all suffixes ending at 'right' for forbidden words
            node = trie
            # Iterate backwards from right, limited by max_len and current left
            for i in range(right, max(left - 1, right - max_len), -1):
                ch = word[i]
                if ch not in node:
                    break
                node = node[ch]
                if '#' in node:
                    # Forbidden word found from i to right -> move left past it
                    left = i + 1
                    break
            ans = max(ans, right - left + 1)
        return ans