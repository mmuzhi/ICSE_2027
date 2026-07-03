class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        n = len(word)
        if n == 0:
            return 0
        forbidden_set = set(forbidden)
        max_len = 0
        if not forbidden_set:
            return n
        for i in range(n):
            for j in range(i, n):
                substr = word[i:j+1]
                found = False
                for f in forbidden_set:
                    if len(f) > len(substr):
                        continue
                    if f in substr:
                        found = True
                        break
                if not found:
                    max_len = max(max_len, j - i + 1)
        return max_len