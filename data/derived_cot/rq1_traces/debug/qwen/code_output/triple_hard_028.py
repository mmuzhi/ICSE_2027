import math

mod = 10**9+7

class Solution:
    def countAnagrams(self, s: str) -> int:
        l = s.split()
        ans = 1
        for i in l:
            d = {}
            for char in i:
                d[char] = d.get(char, 0) + 1
            denominator = 1
            for count in d.values():
                denominator *= math.factorial(count)
            n = len(i)
            numerator = math.factorial(n)
            curr = numerator // denominator
            ans = (ans * curr) % mod
        return ans