#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>

template <typename T>
class AvgPartition {
private:
    std::vector<T> lst;
    int limit;

public:
    // Initialize the class with the given list and the number of partitions
    AvgPartition(std::vector<T> lst, int limit) : lst(std::move(lst)), limit(limit) {}

    // Calculate the size of each block and the remainder of the division.
    // Returns a pair representing (size, remainder).
    std::pair<int, int> setNum() const {
        if (limit == 0) {
            // Mimic Python's ZeroDivisionError to prevent C++ undefined behavior
            throw std::overflow_error("integer division or modulo by zero");
        }
        int n = static_cast<int>(lst.size());
        int size = n / limit;
        int remainder = n % limit;
        return {size, remainder};
    }

    // Calculate the corresponding start and end positions based on the index of the partition.
    // Returns the corresponding block as a vector.
    std::vector<T> get(int index) const {
        auto [size, remainder] = setNum();
        
        int start = index * size + std::min(index, remainder);
        int end = start + size;
        
        if (index + 1 <= remainder) {
            end += 1;
        }
        
        // Mimic Python's safe out-of-bounds slicing (e.g., lst[10:20] on a list of size 4 returns [])
        int n = static_cast<int>(lst.size());
        int s = std::max(0, std::min(start, n));
        int e = std::max(0, std::min(end, n));
        
        // If start >= end, Python slicing returns an empty list
        if (s >= e) {
            return {};
        }
        
        return std::vector<T>(lst.begin() + s, lst.begin() + e);
    }
};