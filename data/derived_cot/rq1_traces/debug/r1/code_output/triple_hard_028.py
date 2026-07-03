import math
mod = 10**9 + 7

class Solution:
    def countAnagrams(self, s: str) -> int:
        l = s.split()
        ans = 1

        for word in l:
            freq = {}
            for char in word:
                if char in freq:
                    freq[char] += 1
                else:
                    freq[char] = 1
            
            denominator = 1
            for count in freq.values():
                denominator *= math.factorial(count)
            
            numerator = math.factorial(len(word))
            ans = (ans * (numerator // denominator)) % mod

        return ans