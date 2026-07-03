class Solution:
    def longestWPI(self, A):
        curr, ans, D = 0, 0, {}
        for e, i in enumerate(self.transform(A)):
            curr += i
            D[curr] = D.get(curr, e)
            if curr > 0:
                ans = e + 1
            else:
                ans = max(ans, e - D.get(curr - 1, e))
        return ans
    
    def transform(self, A):
        return [1 if x > 8 else -1 for x in A]