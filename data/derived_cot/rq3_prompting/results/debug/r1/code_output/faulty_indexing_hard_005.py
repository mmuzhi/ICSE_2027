from typing import List
import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words or not words[0]:
            return []
        wlen = len(words[0])
        slen = wlen * len(words)
        if len(s) < slen:
            return []
        occ = collections.Counter(words)
        track = {}
        
        def test():
            for key, val in track.items():
                if val != occ.get(key, 0):
                    return False
            # ensure all words from occ are present in track
            for key in occ:
                if key not in track:
                    return False
            return True
        
        res = []
        for k in range(wlen):
            if k + slen > len(s):
                break
            # reset track
            track.clear()
            for word in words:
                track[word] = 0
            # build first window
            for i in range(k, k + slen, wlen):
                w = s[i:i+wlen]
                if w in words:
                    track[w] += 1
            if test():
                res.append(k)
            # slide the window
            for i in range(k + wlen, len(s) - slen + 1, wlen):
                # remove left word
                pw = s[i - wlen:i]
                if pw in words:
                    track[pw] -= 1
                # add right word
                nw = s[i + slen - wlen:i + slen]
                if nw in words:
                    track[nw] += 1
                if test():
                    res.append(i)   # fixed: use i instead of i+wlen
        return res