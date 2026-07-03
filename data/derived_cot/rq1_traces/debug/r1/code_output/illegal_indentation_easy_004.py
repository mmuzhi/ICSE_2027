from typing import List
from collections import Counter

class Solution:
    def countCharacters(self, words: List[str], chars: str) -> int:
        ans = []
        char_count = Counter(chars)
        for word in words:
            word_count = Counter(word)
            if all(word_count[char] <= char_count.get(char, 0) for char in word_count):
                ans.append(len(word))
        return sum(ans)