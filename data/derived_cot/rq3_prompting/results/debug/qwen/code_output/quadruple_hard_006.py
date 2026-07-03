class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word or not forbidden:
            return 0
        forbidden_set = set(forbidden)
        n = len(word)
        max_len = 0
        for i in range(n):
            j = i
            while j < n:
                substr = word[i:j+1]
                if any(f in substr for f in forbidden_set):
                    break
                j += 1
            max_len = max(max_len, j - i)
        return max_len