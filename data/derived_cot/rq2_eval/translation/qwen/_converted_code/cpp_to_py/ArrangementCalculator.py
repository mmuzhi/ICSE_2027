import itertools

class ArrangementCalculator:
    def __init__(self, datas):
        self.datas = list(datas)
    
    @staticmethod
    def count(n, m=-1):
        if m == -1 or n == m:
            return ArrangementCalculator.factorial(n)
        else:
            return ArrangementCalculator.factorial(n) // ArrangementCalculator.factorial(n - m)
    
    @staticmethod
    def factorial(n):
        if n < 0:
            return 1
        result = 1
        for i in range(2, n+1):
            result *= i
        return result

    def select(self, m=-1):
        if m == -1:
            m = len(self.datas)
        elif m < 0:
            return []
        
        if m == 0:
            return [[]]
        
        if m > len(self.datas):
            return []
        
        result = []
        for p in itertools.permutations(self.datas, m):
            result.append(list(p))
        return result

    def select_all(self):
        result = []
        for r in range(1, len(self.datas)+1):
            partial_result = self.select(r)
            result.extend(partial_result)
        return result