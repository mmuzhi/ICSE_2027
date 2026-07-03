#include <vector>

class ChandrasekharSieve {
private:
    int n;
    std::vector<int> primes;

public:
    // Initialize the ChandrasekharSieve class with the given limit.
    ChandrasekharSieve(int n) : n(n) {
        primes = generate_primes();
    }

    // Generate prime numbers up to the specified limit using the sieve algorithm.
    std::vector<int> generate_primes() {
        if (n < 2) {
            return {};
        }

        std::vector<bool> sieve(n + 1, true);
        sieve[0] = sieve[1] = false;

        // Use long long to prevent integer overflow when calculating p * p
        for (long long p = 2; p * p <= n; ++p) {
            if (sieve[p]) {
                for (long long i = p * p; i <= n; i += p) {
                    sieve[i] = false;
                }
            }
        }

        std::vector<int> result;
        for (int i = 2; i <= n; ++i) {
            if (sieve[i]) {
                result.push_back(i);
            }
        }

        return result;
    }

    // Get the list of generated prime numbers.
    const std::vector<int>& get_primes() const {
        return primes;
    }
};