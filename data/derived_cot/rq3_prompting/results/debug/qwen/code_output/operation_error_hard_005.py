class Solution:
    def productOfDigits(self, n: int) -> int:
        product = 1
        while n:
            product *= n % 10
            n //= 10
        return product

    def maxNiceDivisors(self, primeFactors: int) -> int:
        if primeFactors <= 10:
            for i in range(primeFactors, 0, -1):
                if self.productOfDigits(i) == primeFactors and primeFactors % i == 0:
                    return i
            return -1
        else:
            return -1