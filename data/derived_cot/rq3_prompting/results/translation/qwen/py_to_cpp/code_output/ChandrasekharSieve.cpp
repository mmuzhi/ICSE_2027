#include <vector>
#include <cmath>

class ChandrasekharSieve {
public:
    ChandrasekharSieve(int n) {
        this->n = n;
        generate_primes();
    }

    std::vector<int> get_primes() const {
        return primes;
    }

private:
    void generate_primes() {
        if (n < 2) {
            primes = {};
            return;
        }

        std::vector<bool> sieve(n + 1, true);
        sieve[0] = false;
        sieve[1] = false;

        for (int p = 2; p * p <= n; ++p) {
            if (sieve[p]) {
                for (int j = p * p; j <= n; j += p) {
                    sieve[j] = false;
                }
            }
        }

        primes.reserve(n / log(n)); // Reserve approximate space for primes
        for (int i = 2; i <= n; ++i) {
            if (sieve[i]) {
                primes.push_back(i);
            }
        }
    }

    int n;
    std::vector<int> primes;
};