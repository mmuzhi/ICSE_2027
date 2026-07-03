import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        word_len = len(words[0])
        total_len = word_len * len(words)
        n = len(s)
        if n < total_len:
            return []
        occ = collections.Counter(words)
        res = []
        for start in range(0, n - total_len + 1):
            window_words = []
            for i in range(len(words)):
                end_index = start + i * word_len + word_len
                word = s[start + i * word_len:end_index]
                window_words.append(word)
            window_freq = collections.Counter(window_words)
            if window_freq == occ:
                res.append(start)
        return res