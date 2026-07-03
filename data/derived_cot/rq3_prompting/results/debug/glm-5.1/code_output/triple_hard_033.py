from typing import List
import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words or not s:
            return []
        wlen = len(words[0])
        slen = wlen * len(words)
        track = dict()
        
        occ = collections.Counter(words)

        def test():
            for key, val in occ.items():
                if track.get(key, 0) != val:
                    return False 
            return True

        res = []

        for k in range(wlen):
            track = {i: 0 for i in occ}
            if k + slen > len(s):
                continue
            for i in range(k, slen + k, wlen):
                w = s[i:i+wlen]
                if w in occ:
                    track[w] += 1
            if test():
                res.append(k)
            
            for i in range(wlen + k, len(s) - slen + 1, wlen):
                nw = s[i + slen - wlen : i + slen]
                pw = s[i - wlen : i]
                if nw in occ:
                    track[nw] += 1
                if pw in occ:
                    track[pw] -= 1
                if test():
                    res.append(i)
                    
        return res