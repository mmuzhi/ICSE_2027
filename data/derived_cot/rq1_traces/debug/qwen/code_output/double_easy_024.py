class Solution:
    def sortString(self, s: str) -> str:
        freq = {}
        for i in s:
            freq[i] = freq.get(i, 0) + 1
        letters = sorted(freq.keys())
        res = ""
        while freq:
            for i in letters:
                if freq[i] > 0:
                    res += i
                    freq[i] -= 1
            for i in letters[::-1]:
                if freq[i] > 0:
                    res += i
                    freq[i] -= 1
        return res