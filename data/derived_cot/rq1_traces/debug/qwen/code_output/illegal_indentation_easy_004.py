from collections import Counter

class Solution:
    def countCharacters(self, words: List[str], chars: str) -> int:
        d1 = Counter(chars)
        ans = 0
        for word in words:
            d2 = Counter(word)
            valid = True
            for char, count in d2.items():
                if char not in d1 or count > d1[char]:
                    valid = False
                    break
            if valid:
                ans += len(word)
        return ans