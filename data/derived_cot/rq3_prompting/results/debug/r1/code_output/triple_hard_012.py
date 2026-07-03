from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        # Build trie of forbidden words (forward)
        trie = {}
        for f in forbidden:
            node = trie
            for ch in f:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node['#'] = True  # end marker

        max_len = max((len(f) for f in forbidden), default=0)
        left = 0
        res = 0

        for right in range(len(word)):
            node = trie
            # Check substrings ending at 'right' from shortest to longest
            limit = min(max_len, right - left + 1)
            for depth in range(limit):
                ch = word[right - depth]
                if ch not in node:
                    break
                node = node[ch]
                if '#' in node:
                    # Forbidden word found; adjust left boundary
                    left = max(left, right - depth + 1)
                    break  # longest start (closest to right) already handled

            res = max(res, right - left + 1)

        return res