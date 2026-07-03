class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        before = 0
        after = len(s) - 1
        l = list(s)                     # simpler than comprehension
        while before <= len(s) // 2:    # use integer division for clarity
            l[before] = min(l[before], l[after])
            l[after] = l[before]
            before += 1
            after -= 1
        return "".join(l)