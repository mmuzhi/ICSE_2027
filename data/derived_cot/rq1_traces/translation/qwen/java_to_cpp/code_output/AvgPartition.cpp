#include <vector>
#include <array>
#include <iostream>

class AvgPartition {
public:
    using ListType = std::vector<int>;

    AvgPartition(ListType lst, int limit) : lst(std::move(lst)), limit(limit) {}

    std::array<int, 2> setNum() const {
        int size = lst.size() / limit;
        int remainder = lst.size() % limit;
        return {size, remainder};
    }

    ListType get(int index) const {
        auto nums = setNum();
        int base_size = nums[0];
        int remainder = nums[1];
        int start = index * base_size + (index < remainder ? index : remainder);
        int end = start + base_size;
        if (index < remainder) {
            end++;
        }
        return ListType(lst.begin() + start, lst.begin() + end);
    }

    static void main() {
        ListType lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(4);
        AvgPartition a(lst, 2);
        ListType part0 = a.get(0);
        ListType part1 = a.get(1);
        std::cout << "[";
        for (size_t i = 0; i < part0.size(); ++i) {
            std::cout << part0[i];
            if (i < part0.size() - 1) std::cout << ",";
        }
        std::cout << "]";
        std::cout << "\n[";
        for (size_t i = 0; i < part1.size(); ++i) {
            std::cout << part1[i];
            if (i < part1.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }
};

int main() {
    AvgPartition::main();
    return 0;
}