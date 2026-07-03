#include <iostream>
#include <vector>
#include <algorithm> // for std::min

class AvgPartition {
private:
    std::vector<int> lst;
    int limit;

public:
    AvgPartition(const std::vector<int>& lst, int limit) : lst(lst), limit(limit) {}

    // Returns {size, remainder}
    std::vector<int> setNum() {
        int size = lst.size() / limit;
        int remainder = lst.size() % limit;
        return {size, remainder};
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
        // Return a copy of the subrange (behaves like Java's subList for this use case)
        return std::vector<int>(lst.begin() + start, lst.begin() + end);
    }

    static void main() {
        std::vector<int> lst = {1, 2, 3, 4};
        AvgPartition a(lst, 2);

        std::vector<int> sub0 = a.get(0);
        std::cout << "[";
        for (size_t i = 0; i < sub0.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << sub0[i];
        }
        std::cout << "]" << std::endl;

        std::vector<int> sub1 = a.get(1);
        std::cout << "[";
        for (size_t i = 0; i < sub1.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << sub1[i];
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    AvgPartition::main();
    return 0;
}