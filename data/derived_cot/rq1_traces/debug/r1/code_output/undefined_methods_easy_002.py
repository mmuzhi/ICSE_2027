class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        before = 0
        after = len(s)-1
        l = list(s)
        while before < after:
            min_char = min(l[before], l[after])
            l[before] = min_char
            l[after] = min_char
            before += 1
            after -= 1
        return "".join(l)