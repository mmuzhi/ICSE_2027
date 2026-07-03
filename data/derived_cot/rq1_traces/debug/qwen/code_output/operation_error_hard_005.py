class Solution:
    def maxNiceDivisors(self, primeFactors: int) -> int:
        if primeFactors <= 1:
            return -1
        
        MOD = int(1e9 + 7)
        if primeFactors % 3 == 0:
            power = primeFactors // 3
            return self.calculateNiceDivisors(3, power, MOD) * 2
        elif primeFactors % 3 == 1:
            power = (primeFactors // 3) - 1
            return (self.calculateNiceDivisors(3, power, MOD) * 4) % MOD
        else:
            power = primeFactors // 3
            return (self.calculateNiceDivisors(3, power, MOD) * 2) % MOD
    
    def calculateNiceDivisors(self, base: int, power: int, MOD: int) -> int:
        return pow(base, power, MOD)