class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        from collections import Counter
        freq = Counter(s)
        n = len(s)
        res = [''] * n
        
        for i in range(n):
            if i < n - i - 1:
                if freq['a'] >= 2:
                    res[i] = 'a'
                    res[n - i - 1] = 'a'
                    freq['a'] -= 2
                else:
                    for char in sorted(freq.keys()):
                        if freq[char] >= 1:
                            if i < n - i - 1 and freq[char] >= 2:
                                res[i] = char
                                res[n - i - 1] = char
                                freq[char] -= 2
                                break
                            elif i == n - i - 1 and freq[char] >= 1:
                                res[i] = char
                                freq[char] -= 1
                                break
            else:
                for char in sorted(freq.keys()):
                    if freq[char] >= 1:
                        res[i] = char
                        freq[char] -= 1
                        break
        
        return ''.join(res)