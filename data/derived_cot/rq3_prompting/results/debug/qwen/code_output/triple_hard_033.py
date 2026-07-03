import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words:
            return []
        wlen = len(words[0])
        slen = wlen * len(words)
        if len(s) < slen:
            return []
        
        occ = collections.Counter(words)
        res = []
        
        def test():
            for key in occ:
                if key not in track or track[key] != occ[key]:
                    return False
            return True
        
        for k in range(wlen):
            track = collections.Counter()
            valid = True
            for i in range(k, k + slen, wlen):
                word = s[i:i+wlen]
                if word in occ:
                    track[word] += 1
                else:
                    valid = False
                    break
            if valid and test():
                res.append(k)
            
            for i in range(k + wlen, len(s) - slen + 1, wlen):
                word_out = s[i - wlen:i]
                if word_out in occ:
                    track[word_out] -= 1
                word_in = s[i + slen - wlen:i + slen]
                if word_in in occ:
                    track[word_in] += 1
                if test():
                    res.append(i - wlen)
        return res