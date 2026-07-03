class Solution:
    def sortString(self, s: str) -> str:
        freq = {}
        letters = sorted(set(s))
        res = ""
        for char in s:
            freq[char] = freq.get(char, 0) + 1
        
        while freq:
            for i in letters:
                if i in freq and freq[i] > 0:
                    res += i
                    freq[i] -= 1
                    if freq[i] == 0:
                        del freq[i]
            for i in reversed(letters):
                if i in freq and freq[i] > 0:
                    res += i
                    freq[i] -= 1
                    if freq[i] == 0:
                        del freq[i]
        return res