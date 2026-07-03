from typing import List
import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words or not s:
            return []
            
        wlen = len(words[0])
        slen = wlen * len(words)
        occ = collections.Counter(words)
        res = []
        
        for k in range(wlen):
            if k + slen > len(s):
                break
            
            track = {w: 0 for w in occ}
            for i in range(k, slen + k, wlen):
                w = s[i:i+wlen]
                if w in track:
                    track[w] += 1
            if track == occ:
                res.append(k)
                
            for start in range(k + wlen, len(s) - slen + 1, wlen):
                pw = s[start - wlen:start]
                nw = s[start + slen - wlen:start + slen]
                
                if pw in track:
                    track[pw] -= 1
                if nw in track:
                    track[nw] += 1
                    
                if track == occ:
                    res.append(start)
                    
        return res