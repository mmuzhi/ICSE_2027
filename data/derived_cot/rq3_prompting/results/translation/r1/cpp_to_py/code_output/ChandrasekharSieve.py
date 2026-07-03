class ChandrasekharSieve:
    def __init__(self, n: int):
        self._n = n
        self._primes = self._generate_primes()

    def get_primes(self):
        # Return a copy to match C++ const method returning by value
        return list(self._primes)

    def _generate_primes(self):
        n = self._n
        if n < 2:
            return []

        sieve = [True] * (n + 1)
        sieve[0] = sieve[1] = False

        p = 2
        while p * p <= n:
            if sieve[p]:
                for i in range(p * p, n + 1, p):
                    sieve[i] = False
            p += 1

        primes = [i for i in range(2, n + 1) if sieve[i]]
        return primes