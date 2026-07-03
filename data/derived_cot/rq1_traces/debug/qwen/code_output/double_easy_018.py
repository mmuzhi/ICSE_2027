from collections import Counter

class Solution:
    def countCharacters(self, words: List[str], chars: str) -> int:
        d1 = Counter(chars)
        ans = 0
        for word in words:
            d2 = Counter(word)
            if all(d2[char] <= d1[char] for char in d2):
                ans += len(word)
        return ans