#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <limits>

class AvgPartition {
private:
    std::vector<int>& lst;
    int limit;

public:
    AvgPartition(std::vector<int>& lst, int limit) : lst(lst), limit(limit) {}

    std::vector<int> get(int index) {
        if (limit <= 0) {
            throw std::runtime_error("limit must be positive");
        }

        if (index < 0 || index >= limit) {
            throw std::out_of_range("index must be in range [0, " + std::to_string(limit-1) + "]");
        }

        if (lst.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
            throw std::runtime_error("list size too large");
        }
        int n = static_cast<int>(lst.size());
        int size = n / limit;
        int remainder = n % limit;

        int start = index * size + std::min(index, remainder);
        int end = start + size;
        if (index < remainder) {
            end += 1;
        }

        if (start > n || end > n || start < 0) {
            throw std::out_of_range("computed indices are out of range");
        }

        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }
};

int main() {
    std::vector<int> lst = {1, 2, 3, 4};
    AvgPartition a(lst, 2);
    std::vector<int> part0 = a.get(0);
    std::vector<int> part1 = a.get(1);

    auto printVector = [](const std::vector<int>& vec) {
        std::cout << "[";
        for (int i = 0; i < vec.size(); i++) {
            std::cout << vec[i];
            if (i != vec.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
    };

    printVector(part0);
    std::cout << std::endl;
    printVector(part1);
    std::cout << std::endl;

    return 0;
}