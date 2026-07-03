import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words or not s:
            return []
        wlen = len(words[0])
        n = len(words)
        total_len = wlen * n
        if len(s) < total_len:
            return []
        
        word_count = collections.Counter(words)
        res = []
        
        for k in range(wlen):
            if k + total_len > len(s):
                continue
                
            current_count = collections.Counter()
            for j in range(n):
                word = s[k + j * wlen : k + j * wlen + wlen]
                current_count[word] += 1
                
            if current_count == word_count:
                res.append(k)
                
            start = k
            next_start = k + wlen
            while next_start + total_len <= len(s):
                first_word = s[start:start+wlen]
                current_count[first_word] -= 1
                new_word = s[start+total_len:start+total_len+wlen]
                current_count[new_word] += 1
                
                if current_count == word_count:
                    res.append(next_start)
                
                start = next_start
                next_start = start + wlen
        
        return res