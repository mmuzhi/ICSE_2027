class Solution:
    def checkValidString(self, s):
        low, high = 0, 0
        for c in s:
            if c == '(':
                low += 1
                high += 1
            elif c == ')':
                low -= 1
                high -= 1
            else:  # c == '*'
                low = max(low - 1, 0)
                high += 1
            if low < 0 or high < 0:
                return False
        return low == 0