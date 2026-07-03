class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words or not s:
            return []
        wlen = len(words[0])
        total_length = wlen * len(words)
        if len(s) < total_length:
            return []
        
        occ = collections.Counter(words)
        res = []
        
        for k in range(wlen):
            if k + total_length > len(s):
                continue
            track = {word: 0 for word in occ}
            
            for i in range(k, k + total_length, wlen):
                word_segment = s[i:i + wlen]
                if word_segment in occ:
                    track[word_segment] += 1
            
            def test():
                for key, val in track.items():
                    if val != occ[key]:
                        return False
                return True
            
            if test():
                res.append(k)
            
            for i in range(k + wlen, len(s) - total_length + 1, wlen):
                prev_word = s[i - wlen:i]
                next_word = s[i + total_length - wlen:i + total_length]
                
                if prev_word in occ:
                    track[prev_word] -= 1
                if next_word in occ:
                    track[next_word] += 1
                
                if test():
                    res.append(i)
        
        return res