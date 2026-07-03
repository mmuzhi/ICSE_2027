class ChandrasekharSieve:
    def __init__(self, n):
        self.n = n
        self.primes = self._generate_primes()

    def _generate_primes(self):
        if self.n < 2:
            return []
        
        sieve = [True] * (self.n + 1)
        sieve[0] = sieve[1] = False
        
        p = 2
        while p * p <= self.n:
            if sieve[p]:
                start = p * p
                # Mark all multiples of p starting from p*p
                for i in range(start, self.n + 1, p):
                    sieve[i] = False
            p += 1
        
        # Collect all numbers marked True in sieve
        return [i for i, is_prime in enumerate(sieve) if is_prime]