class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        n = len(word)
        if n == 0:
            return 0
        
        forbidden_set = set(forbidden)
        
        i = 0
        j = 0
        max_len = 0
        
        while j < n:
            found = False
            for f in forbidden_set:
                if f in word[i:j+1]:
                    found = True
                    break
            if found:
                i = j + 1
            else:
                max_len = max(max_len, j - i + 1)
                j += 1
        
        return max_len