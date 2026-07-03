import math

mod = 10**9 + 7

class Solution:
    def countAnagrams(self, s: str) -> int:
        l = s.split()
        ans = 1
        
        for i in l:
            d = {}
            for j in i:
                if j in d:
                    d[j] += 1
                else:
                    d[j] = 1
            
            duplicates = 1
            for count in d.values():
                duplicates *= math.factorial(count)
            
            curr = math.factorial(len(i)) // duplicates
            ans = (ans * curr) % mod
        
        return ans