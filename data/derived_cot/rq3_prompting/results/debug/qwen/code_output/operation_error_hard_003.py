import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words:
            return []
        wlen = len(words[0])
        slen = wlen * len(words)
        if slen > len(s):
            return []
        
        occ = collections.Counter(words)
        res = []
        
        def test():
            for key in occ:
                if track[key] != occ[key]:
                    return False
            return True
        
        for k in range(wlen):
            if k + slen > len(s):
                continue
            track = {}
            for word in words:
                track[word] = 0
            
            for i in range(k, k + slen, wlen):
                word = s[i:i+wlen]
                if word in track:
                    track[word] += 1
            
            if test():
                res.append(k)
            
            for i in range(wlen + k, len(s) - slen + 1, wlen):
                leaving_word = s[i - wlen:i]
                entering_word = s[i + slen:i + slen + wlen]
                
                if leaving_word in track:
                    track[leaving_word] -= 1
                if entering_word in track:
                    track[entering_word] += 1
                
                if test():
                    res.append(i - wlen)
        return res