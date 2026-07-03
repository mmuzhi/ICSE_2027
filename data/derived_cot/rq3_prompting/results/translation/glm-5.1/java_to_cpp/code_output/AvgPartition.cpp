#include <iostream>
#include <vector>
#include <algorithm>

class AvgPartition {
private:
    std::vector<int> lst;
    int limit;

public:
    AvgPartition(std::vector<int> lst, int limit) : lst(lst), limit(limit) {}

    std::vector<int> setNum() {
        int size = static_cast<int>(lst.size()) / limit;
        int remainder = static_cast<int>(lst.size()) % limit;
        return std::vector<int>{size, remainder};
    }

    std::vector<int> get(int index) {
        std::vector<int> nums = setNum();
        int size = nums[0];
        int remainder = nums[1];
        int start = index * size + std::min(index, remainder);
        int end = start + size;
        if (index + 1 <= remainder) {
            end += 1;
        }
        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }
};

int main() {
    std::vector<int> lst = {1, 2, 3, 4};
    AvgPartition a(lst, 2);
    auto v0 = a.get(0);
    auto v1 = a.get(1);
    std::cout << "[";
    for (size_t i = 0; i < v0.size(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << v0[i];
    }
    std::cout << "]" << std::endl;
    std::cout << "[";
    for (size_t i = 0; i < v1.size(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << v1[i];
    }
    std::cout << "]" << std::endl;
    return 0;
}