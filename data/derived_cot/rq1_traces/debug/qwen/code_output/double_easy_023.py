class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        l = list(s)
        left = 0
        right = len(s) - 1
        while left < right:
            l[left] = min(l[left], l[right])
            l[right] = min(l[left], l[right])
            left += 1
            right -= 1
        return "".join(l)