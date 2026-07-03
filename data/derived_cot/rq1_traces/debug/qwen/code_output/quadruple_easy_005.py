class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        l = list(s)
        before = 0
        after = len(l) - 1
        while before < after:
            if l[before] != l[after]:
                m = min(l[before], l[after])
                l[before] = m
                l[after] = m
            before += 1
            after -= 1
        return "".join(l)