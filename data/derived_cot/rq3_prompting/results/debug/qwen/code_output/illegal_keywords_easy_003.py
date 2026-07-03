class Solution:
    def firstPalindrome(self, words) -> str:
        for i in words:
            if i == i[::-1]:
                return i
        return ""