class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s)
        mod = 10**9 + 7
        
        # Fenwick tree implementation
        class Fenw:
            def __init__(self, size):
                self.n = size
                self.tree = [0] * (self.n + 1)
            
            def update(self, index, delta):
                i = index + 1
                while i <= self.n:
                    self.tree[i] += delta
                    i += i & -i
            
            def query(self, index):
                res = 0
                i = index + 1
                while i:
                    res += self.tree[i]
                    i -= i & -i
                return res
        
        # Initialize Fenwick tree for numbers 0 to n
        fenw = Fenw(n)
        
        # dp[i] = number of ways to have built the first i+1 elements
        dp = [0] * (n + 1)
        dp[0] = 1
        
        for char in s:
            new_dp = [0] * (n + 1)
            if char == 'I':
                for i in range(n + 1):
                    if dp[i] == 0:
                        continue
                    # Count available numbers greater than i
                    available = fenw.query(n) - fenw.query(i)
                    if available == 0:
                        continue
                    for j in range(i + 1, n + 1):
                        if fenw.query(j) - fenw.query(j - 1) == 0:
                            new_dp[j] = (new_dp[j] + dp[i]) % mod
            else:
                for i in range(n + 1):
                    if dp[i] == 0:
                        continue
                    # Count available numbers less than i
                    available = fenw.query(i - 1)
                    if available == 0:
                        continue
                    for j in range(0, i):
                        if fenw.query(j) - fenw.query(j - 1) == 0:
                            new_dp[j] = (new_dp[j] + dp[i]) % mod
            dp = new_dp
        
        return sum(dp) % mod