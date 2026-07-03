class Solution:
    def maxNiceDivisors(self, primeFactors: int) -> int:
        if primeFactors <= 3:
            return primeFactors
        
        MOD = int(1e9 + 7)
        if primeFactors % 3 == 0:
            power = primeFactors // 3
            return self.calculateNiceDivisors(3, power, MOD)
        elif primeFactors % 3 == 1:
            power = (primeFactors // 3) - 1
            return (self.calculateNiceDivisors(3, power, MOD) * 4) % MOD
        else:
            power = primeFactors // 3
            return (self.calculateNiceDivisors(3, power, MOD) * 2) % MOD

    def calculateNiceDivisors(self, base: int, power: int, MOD: int) -> int:
        result = 1
        while power:
            if power % 2 == 1:
                result = (result * base) % MOD
            base = (base * base) % MOD
            power //= 2
        return result