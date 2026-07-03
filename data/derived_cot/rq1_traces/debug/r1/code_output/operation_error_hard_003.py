class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        wlen = len(words[0])
        slen = wlen * len(words)
        track = dict()
        
        occ = collections.Counter(words)

        def test():
            for key, val in track.items():
                if val != occ[key]:
                    return False
            return True

        res = []

        for k in range(wlen):
            for word in words:
                track[word] = 0
            for i in range(k, k + slen, wlen):
                if i + wlen > len(s):
                    break
                w = s[i:i + wlen]
                if w in track:
                    track[w] += 1
            if test():
                res.append(k)
            for i in range(k + wlen, len(s) - slen + 1, wlen):
                pw = s[i - wlen:i]
                nw = s[i + slen - wlen:i + slen]
                if nw in track:
                    track[nw] += 1
                if pw in track:
                    track[pw] -= 1
                if test():
                    res.append(i)
        return res