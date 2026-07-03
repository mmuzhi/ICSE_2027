#include <vector>
#include <iostream>

class ChandrasekharSieve {
private:
    int n;
    std::vector<int> primes;

    std::vector<int> generatePrimes() {
        if (n < 2) {
            return std::vector<int>();
        }

        std::vector<bool> sieve(n + 1, true);
        sieve[0] = sieve[1] = false;

        for (int p = 2; p * p <= n; ++p) {
            if (sieve[p]) {
                for (int i = p * p; i <= n; i += p) {
                    sieve[i] = false;
                }
            }
        }

        std::vector<int> primesList;
        for (int i = 2; i <= n; ++i) {
            if (sieve[i]) {
                primesList.push_back(i);
            }
        }

        return primesList;
    }

public:
    ChandrasekharSieve(int n) : n(n), primes(generatePrimes()) {}

    std::vector<int> getPrimes() const {
        return primes;
    }
};

int main() {
    ChandrasekharSieve cs(20);
    std::cout << "[";
    for (size_t i = 0; i < cs.getPrimes().size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << cs.getPrimes()[i];
    }
    std::cout << "]";
    return 0;
}