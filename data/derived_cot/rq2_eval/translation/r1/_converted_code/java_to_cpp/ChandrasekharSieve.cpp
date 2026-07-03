#include <iostream>
#include <vector>
#include <cstring>

class ChandrasekharSieve {
private:
    int n;
    std::vector<int> primes;

    std::vector<int> generatePrimes() {
        if (n < 2) {
            return std::vector<int>();
        }

        std::vector<bool> sieve(n + 1, true);
        sieve[0] = false;
        sieve[1] = false;

        int p = 2;
        while (p * p <= n) {
            if (sieve[p]) {
                for (int i = p * p; i <= n; i += p) {
                    sieve[i] = false;
                }
            }
            p++;
        }

        std::vector<int> primes_list;
        for (int i = 2; i <= n; i++) {
            if (sieve[i]) {
                primes_list.push_back(i);
            }
        }

        return primes_list;
    }

public:
    ChandrasekharSieve(int n) : n(n) {
        primes = generatePrimes();
    }

    std::vector<int> getPrimes() {
        return primes;
    }
};

int main() {
    ChandrasekharSieve cs(20);
    std::vector<int> primes = cs.getPrimes();
    std::cout << "[";
    if (!primes.empty()) {
        std::cout << primes[0];
        for (size_t i = 1; i < primes.size(); ++i) {
            std::cout << ", " << primes[i];
        }
    }
    std::cout << "]" << std::endl;
    return 0;
}