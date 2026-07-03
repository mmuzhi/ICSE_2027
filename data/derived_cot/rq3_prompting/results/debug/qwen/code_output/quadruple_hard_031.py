class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        n = len(word)
        if not forbidden:
            return n
        
        max_len = 0
        left = 0
        for right in range(n):
            found = False
            for f in forbidden:
                if f in word[left:right+1]:
                    start_index = word[left:right+1].index(f)
                    left = start_index + len(f) + 1
                    found = True
                    break
            if not found:
                max_len = max(max_len, right - left + 1)
        return max_len