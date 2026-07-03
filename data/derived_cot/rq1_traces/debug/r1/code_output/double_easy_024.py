class Solution:
    def sortString(self, s: str) -> str:
        freq = {}
        letters = sorted(set(s))
        res = ""
        for char in s:
            freq[char] = freq.get(char, 0) + 1
        while freq:
            for char in letters:
                if char in freq:
                    res += char
                    freq[char] -= 1
                    if freq[char] == 0:
                        del freq[char]
            for char in letters[::-1]:
                if char in freq:
                    res += char
                    freq[char] -= 1
                    if freq[char] == 0:
                        del freq[char]
        return res