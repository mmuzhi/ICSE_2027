import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words:
            return []
        wlen = len(words[0])
        n = len(words)
        total_len = n * wlen
        if len(s) < total_len:
            return []
        occ = collections.Counter(words)
        res = []
        for k in range(wlen):
            if k + total_len > len(s):
                continue
            cur = {word: 0 for word in occ}
            for i in range(k, k + total_len, wlen):
                word = s[i:i + wlen]
                if word in occ:
                    cur[word] += 1
            if cur == occ:
                res.append(k)
            start0 = k
            while start0 + wlen + total_len <= len(s):
                leave_word = s[start0:start0 + wlen]
                enter_word = s[start0 + total_len:start0 + total_len + wlen]
                if leave_word in occ:
                    cur[leave_word] -= 1
                if enter_word in occ:
                    cur[enter_word] += 1
                if cur == occ:
                    res.append(start0 + wlen)
                start0 += wlen
        return res