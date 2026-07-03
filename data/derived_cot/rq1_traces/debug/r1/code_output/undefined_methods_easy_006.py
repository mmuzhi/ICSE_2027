class Solution:
    def fib(self, n: int) -> int:
        if n == 0:
            return 0
        if n == 1:
            return 1
        Fib = [-1] * (n + 1)
        Fib[0] = 0
        Fib[1] = 1
        
        def helper(x):
            if Fib[x] != -1:
                return Fib[x]
            Fib[x] = helper(x-1) + helper(x-2)
            return Fib[x]
        
        return helper(n)