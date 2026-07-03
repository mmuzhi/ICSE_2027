class Solution:
    def fib(self, n: int) -> int:
        if hasattr(self, 'Fib_dict') and n in self.Fib_dict:
            return self.Fib_dict[n]
        if not hasattr(self, 'Fib_dict'):
            self.Fib_dict = {}
        if n == 0:
            self.Fib_dict[0] = 0
            return 0
        if n == 1:
            self.Fib_dict[1] = 1
            return 1
        if 0 not in self.Fib_dict:
            self.Fib_dict[0] = 0
        if 1 not in self.Fib_dict:
            self.Fib_dict[1] = 1
        self.Fib_dict[n] = self.fib(n-1) + self.fib(n-2)
        return self.Fib_dict[n]