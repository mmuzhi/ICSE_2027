from typing import List

class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not forbidden:
            return len(word)
        forbidden_set = set(forbidden)
        max_len = max(len(f) for f in forbidden)
        left = 0
        ans = 0
        for right in range(len(word)):
            # Check substrings ending at right, from shortest to longest
            for length in range(1, min(right - left + 1, max_len) + 1):
                substr = word[right - length + 1 : right + 1]
                if substr in forbidden_set:
                    left = max(left, right - length + 2)
                    # Shorter substrings give the largest left bound, so we can stop
                    break
            ans = max(ans, right - left + 1)
        return ans