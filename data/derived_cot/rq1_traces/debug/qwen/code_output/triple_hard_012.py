class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word or not forbidden:
            return 0
        
        max_len_forbidden = max(len(f) for f in forbidden)
        forbidden_set = set(forbidden)
        
        n = len(word)
        i = 0
        j = 0
        max_length = 0
        
        while j < n:
            start = max(i, j - max_len_forbidden + 1)
            new_i = i
            for k in range(start, j + 1):
                substr = word[k:j + 1]
                if substr in forbidden_set:
                    new_i = max(new_i, k + 1)
            i = new_i
            max_length = max(max_length, j - i + 1)
            j += 1
            
        return max_length