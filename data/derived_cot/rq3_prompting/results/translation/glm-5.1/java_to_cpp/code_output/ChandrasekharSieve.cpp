#include <iostream>
#include <vector>

class ChandrasekharSieve {
private:
    int n;
    std::vector<int> primes;

    std::vector<int> generatePrimes() {
        if (n < 2) {
            return {};
        }

        std::vector<bool> sieve(n + 1, true);
        sieve[0] = sieve[1] = false;

        int p = 2;
        while (p * p <= n) {
            if (sieve[p]) {
                for (int i = p * p; i <= n; i += p) {
                    sieve[i] = false;
                }
            }
            ++p;
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

    std::vector<int> getPrimes() {
        return primes;
    }
};

int main() {
    ChandrasekharSieve cs(20);
    std::vector<int> primes = cs.getPrimes();
    
    std::cout << "[";
    for (size_t i = 0; i < primes.size(); ++i) {
        std::cout << primes[i];
        if (i < primes.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}