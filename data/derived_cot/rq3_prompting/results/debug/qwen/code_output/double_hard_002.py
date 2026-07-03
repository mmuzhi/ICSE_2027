import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        wlen = len(words[0])
        n = len(s)
        m = len(words)
        total_len = wlen * m
        if n < total_len:
            return []
        words_freq = collections.Counter(words)
        res = []
        
        for start_index in range(0, n - total_len + 1):
            freq = collections.Counter()
            for j in range(start_index, start_index + total_len, wlen):
                word = s[j:j+wlen]
                freq[word] += 1
            if freq == words_freq:
                res.append(start_index)
        return res