from typing import List
from collections import Counter

class Solution:
    def countCharacters(self, words: List[str], chars: str) -> int:
        ans = []
        char_count = Counter(chars)
        for word in words:
            word_count = Counter(word)
            if all(k in char_count for k in word_count) and all(word_count[k] <= char_count[k] for k in word_count):
                ans.append(len(word))
        return sum(ans)