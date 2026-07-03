from typing import List
import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        wlen = len(words[0])
        slen = wlen * len(words)
        if len(s) < slen:
            return []
        occ = collections.Counter(words)
        res = []
        track = {}

        def test() -> bool:
            return track == occ

        for k in range(wlen):
            # reset the tracker for this offset
            for word in words:
                track[word] = 0
            # skip offsets where the full window doesn't fit
            if k + slen > len(s):
                continue

            # build the initial window
            for i in range(k, k + slen, wlen):
                w = s[i:i+wlen]
                if w in words:
                    track[w] += 1
            if test():
                res.append(k)

            # slide the window
            for i in range(k + wlen, len(s) - slen + 1, wlen):
                nw = s[i + slen - wlen : i + slen]   # new word entering
                pw = s[i - wlen : i]                 # old word leaving
                if nw in words:
                    track[nw] += 1
                if pw in words:
                    track[pw] -= 1
                if test():
                    res.append(i)

        return res