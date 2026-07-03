class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        l = list(s)
        before = 0
        after = len(l) - 1
        while before < after:
            min_char = min(l[before], l[after])
            l[before] = l[after] = min_char
            before += 1
            after -= 1
        return ''.join(l)