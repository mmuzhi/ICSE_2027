#include <vector>
#include <cmath>
#include <iostream>

class ChandrasekharSieve {
private:
    int n;
    std::vector<int> primes;

public:
    ChandrasekharSieve(int n) : n(n) {
        primes = generate_primes();
    }

    std::vector<int> generate_primes() {
        if (n < 2) {
            return std::vector<int>();
        }

        std::vector<bool> sieve(n+1, true);
        sieve[0] = false;
        sieve[1] = false;

        int sqrt_n = static_cast<int>(std::sqrt(n));
        for (int p = 2; p <= sqrt_n; ++p) {
            if (sieve[p]) {
                for (int i = p * p; i <= n; i += p) {
                    sieve[i] = false;
                }
            }
        }

        std::vector<int> primes_list;
        for (int i = 2; i <= n; ++i) {
            if (sieve[i]) {
                primes_list.push_back(i);
            }
        }

        return primes_list;
    }

    std::vector<int> get_primes() const {
        return primes;
    }
};