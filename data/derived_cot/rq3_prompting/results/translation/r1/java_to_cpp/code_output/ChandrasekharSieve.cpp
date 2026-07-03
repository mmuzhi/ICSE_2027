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

        std::vector<char> sieve(n + 1, 1);
        sieve[0] = 0;
        sieve[1] = 0;

        int p = 2;
        while (p * p <= n) {
            if (sieve[p]) {
                for (int i = p * p; i <= n; i += p) {
                    sieve[i] = 0;
                }
            }
            p += 1;
        }

        std::vector<int> result;
        for (int i = 2; i <= n; ++i) {
            if (sieve[i]) {
                result.push_back(i);
            }
        }
        return result;
    }

public:
    ChandrasekharSieve(int n) : n(n) {
        primes = generatePrimes();
    }

    std::vector<int>& getPrimes() {
        return primes;
    }

    const std::vector<int>& getPrimes() const {
        return primes;
    }
};

int main() {
    ChandrasekharSieve cs(20);
    const std::vector<int>& primes = cs.getPrimes();
    std::cout << "[";
    for (size_t i = 0; i < primes.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << primes[i];
    }
    std::cout << "]" << std::endl;
    return 0;
}