class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word or not forbidden:
            return 0
        forbidden_set = set(forbidden)
        n = len(word)
        max_len = 0
        left = 0
        for right in range(n):
            contains_forbidden = False
            for f in forbidden_set:
                if f in word[left:right+1]:
                    contains_forbidden = True
                    break
            if contains_forbidden:
                left = right + 1
            else:
                max_len = max(max_len, right - left + 1)
        return max_len