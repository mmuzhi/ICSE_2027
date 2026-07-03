import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words:
            return []
        wlen = len(words[0])
        n = len(words)
        total_len = wlen * n
        if total_len > len(s):
            return []
        from collections import defaultdict, Counter
        occ = Counter(words)

        def test(track):
            for key in occ:
                if key not in track or track[key] != occ[key]:
                    return False
            return True

        res = []
        for k in range(wlen):
            if k + total_len > len(s):
                continue
            track = defaultdict(int)
            for i in range(k, k + total_len, wlen):
                if i + wlen > len(s):
                    break
                word = s[i:i+wlen]
                if word in occ:
                    track[word] += 1
            if test(track):
                res.append(k)
                
            for i in range(k + wlen, len(s) - total_len + 1, wlen):
                word = s[i - wlen:i - wlen + wlen]
                if word in occ:
                    track[word] -= 1
                word = s[i + total_len - wlen:i + total_len]
                if word in occ:
                    track[word] += 1
                if test(track):
                    res.append(i)
        return res