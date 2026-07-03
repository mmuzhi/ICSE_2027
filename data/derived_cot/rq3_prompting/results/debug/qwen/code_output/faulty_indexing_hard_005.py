from collections import Counter
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        wlen = len(words[0])
        n = len(words)
        total_len = wlen * n
        if len(s) < total_len:
            return []
        
        occ = Counter(words)
        res = []
        
        for i in range(len(s) - total_len + 1):
            track = Counter()
            valid = True
            for j in range(n):
                start_index = i + j * wlen
                if start_index + wlen > len(s):
                    valid = False
                    break
                word = s[start_index:start_index + wlen]
                if word not in occ:
                    valid = False
                    break
                track[word] += 1
            if valid and track == occ:
                res.append(i)
                
        return res